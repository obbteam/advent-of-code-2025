#include "part2.h"

#include <map>
#include <unordered_set>
#include <z3++.h>

#include "LightState.h"
#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    const long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 10, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;

    for (auto &line: lines) {
        size_t sb2 = line.find_last_of(']');
        size_t p1 = sb2 + 2, p2 = line.find_last_of(')');
        size_t cb1 = p2 + 2, cb2 = line.size() - 1;

        auto schematics = getSchematics(line.substr(p1, p2 - p1 + 1));
        auto joltages = getJoltages(line.substr(cb1, cb2 - cb1 + 1));

        auto machine = Machine(joltages, schematics);
        result += solveZ3(machine);
    }

    return result;
}

std::vector<int> Part2::getJoltages(const std::string &str) {
    std::vector<int> joltages;

    std::string curNum;
    for (const auto &c: str) {
        if (isdigit(c)) {
            curNum.push_back(c);
        } else if (c == ',') {
            joltages.emplace_back(std::stoi(curNum));
            curNum.clear();
        }
    }
    joltages.emplace_back(std::stoi(curNum));

    return joltages;
}

std::vector<std::vector<int>> Part2::getSchematics(const std::string &str) {
    std::vector<std::vector<int>> schematics;

    std::vector<int> vec;
    std::string curNum;
    for (const auto &c: str) {
        if (c == ')') {
            vec.emplace_back(std::stoi(curNum));
            schematics.emplace_back(vec);
            vec.clear();
            curNum.clear();
        } else if (isdigit(c)) {
            curNum.push_back(c);
        } else if (c == ',') {
            vec.emplace_back(std::stoi(curNum));
            curNum.clear();
        }
    }

    return schematics;
}


// Returns the cost (sum of presses) or 0 if impossible
long long Part2::solveZ3(const Machine& m) {
    z3::context c;
    z3::optimize opt(c); // Use the 'optimize' solver to find the minimal sum

    // 1. Define Variables
    // We create one integer variable x_i for each button in the schematic.
    std::vector<z3::expr> button_presses;
    for (size_t i = 0; i < m.schematics.size(); ++i) {
        std::string name = "btn_" + std::to_string(i);
        z3::expr x = c.int_const(name.c_str());
        button_presses.push_back(x);

        // Constraint: You cannot press a button a negative amount of times
        opt.add(x >= 0);
    }

    // 2. Define Constraints (The Linear Algebra part)
    // We iterate through every 'slot' (joltages index).
    // The sum of button presses affecting this slot must equal the target joltage.
    for (size_t slot_idx = 0; slot_idx < m.joltages.size(); ++slot_idx) {
        z3::expr sum_for_slot = c.int_val(0);

        // Check every button to see if it contributes to this slot
        for (size_t btn_idx = 0; btn_idx < m.schematics.size(); ++btn_idx) {
            bool affects_this_slot = false;

            // Your schematic structure is vector<vector<int>>, where the inner
            // vector is a list of INDICES modified by that button.
            for (int affected_index : m.schematics[btn_idx]) {
                if (affected_index == slot_idx) {
                    affects_this_slot = true;
                    break;
                }
            }

            if (affects_this_slot) {
                sum_for_slot = sum_for_slot + button_presses[btn_idx];
            }
        }

        // Constraint: Sum of contributions == Target for this slot
        opt.add(sum_for_slot == c.int_val(m.joltages[slot_idx]));
    }

    // 3. Define Objective: Minimize total presses
    z3::expr total_presses = c.int_val(0);
    for (const auto& x : button_presses) {
        total_presses = total_presses + x;
    }
    opt.minimize(total_presses);

    // 4. Solve
    if (opt.check() == z3::sat) {
        z3::model model = opt.get_model();
        long long total_sum = 0;

        // Extract values from the model
        for (const auto& x : button_presses) {
            // Z3 C++ API doesn't have a direct .get_long() on expr,
            // so we use the C-API helper or string conversion for safety.
            z3::expr result = model.eval(x);
            long long val = 0;
            // Use the C API to get 64-bit integer safely
            Z3_get_numeral_int64(c, result, &val);
            total_sum += val;
        }
        return total_sum;
    }

    return 0; // No solution found (unsat)
}