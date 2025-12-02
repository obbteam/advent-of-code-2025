#include "part2.h"

#include <unordered_set>

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto line = AoC::loadInput("input.txt");
    long long result = parseInputAndSolve(line[0]);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 2, 2, result, start, end));

}

long long Part2::findInvalid(const std::string &left, const std::string &right) {
    long long ans = 0;
    std::unordered_set<long long> seen;
    for (long long i = stoll(left); i <= std::stoll(right); ++i) {
        std::string str = std::to_string(i);
        for (int j = 1; j <= str.length() / 2; ++j) {
            auto temp = makeDuplicate(str.substr(0, j), str.length() / j);
            if (str == temp && !seen.contains(i)) {
                seen.insert(i);
                ans += i;
            }
        }
    }
    return ans;
}

std::string Part2::makeDuplicate( const std::string& str, int x )
{
    std::string newstr;
    newstr.reserve(str.length()*x); // prevents multiple reallocations

    for (int i = 0; i < x; ++i) {
        newstr += str;
    }

    return newstr;
}

long long Part2::parseInputAndSolve(const std::string &line) {
    std::vector<std::pair<int, int> > res;
    std::string left, right;
    bool r = false;
    long long ans = 0;

    for (const char &c: line) {
        if (c == ',') {
            ans += findInvalid(left, right);
            left.clear();
            right.clear();
            r = false;
            continue;
        }
        if (c == '-') {
            r = true;
            continue;
        }

        if (r) right += c;
        else left += c;
    }
    ans += findInvalid(left, right);

    return ans;
}
