#include "part1.h"

#include <unordered_set>

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 8, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
    auto coordinates = getCoordinates(lines);

    return makeCircuits(coordinates, 1000);
}

std::vector<Coordinate> Part1::getCoordinates(const std::vector<std::string> &lines) {
    std::vector<Coordinate> coords;
    coords.reserve(lines.size());

    for (const auto &line: lines) {
        const auto firstComma = line.find_first_of(',');
        const auto secondComma = line.find_first_of(',', firstComma + 1);

        coords.emplace_back(
            std::stol(line.substr(0, firstComma)),
            std::stol(line.substr(firstComma + 1, secondComma - firstComma)),
            std::stol(line.substr(secondComma + 1))
        );
    }

    return coords;
}

long long Part1::makeCircuits(const std::vector<Coordinate> &coordinates, int n) {
    // keep distance in the maxHeap
    std::priority_queue<CoordinatesDistance> shortestDistance;
    for (int i = 0; i < coordinates.size(); ++i) {
        for (int j = i + 1; j < coordinates.size(); ++j) {
            shortestDistance.push(
                CoordinatesDistance(
                    calculateDistance(coordinates[i], coordinates[j]),
                    coordinates[i],
                    coordinates[j]
                )
            );
        }
    }

    std::vector<std::unordered_set<Coordinate> > circuits;
    // add shortest distance n times
    for (int i = 0; i < n; i++) {
        auto candidate = shortestDistance.top();
        shortestDistance.pop();
        if (circuits.empty()) {
            std::unordered_set<Coordinate> circuit;
            circuit.insert(candidate.from);
            circuit.insert(candidate.to);
            circuits.emplace_back(circuit);
        } else {
            int fromIdx = -1, toIdx = -1;
            for (int j = 0; j < circuits.size(); ++j) {
                if (circuits[j].contains(candidate.from)) {
                    fromIdx = j;
                }
                if (circuits[j].contains(candidate.to)) {
                    toIdx = j;
                }
                if (fromIdx != -1 && toIdx != -1) break;
            }
            if (fromIdx != -1 && toIdx == -1)
                circuits[fromIdx].insert(candidate.to);
            else if (toIdx != -1 && fromIdx == -1) {
                circuits[toIdx].insert(candidate.from);
            } else if (fromIdx == toIdx && fromIdx == -1) {
                // nothing found
                std::unordered_set<Coordinate> circuit;
                circuit.insert(candidate.from);
                circuit.insert(candidate.to);
                circuits.emplace_back(circuit);
            } else if (fromIdx != toIdx){
                // merge 2 circuits
                auto toRemove = circuits[toIdx];
                circuits[fromIdx].insert(toRemove.begin(), toRemove.end());
                circuits.erase(circuits.begin() + toIdx);
            }
        }
    }
    // calculate final result
    return calculateProductOfTop3(circuits);
}


long long Part1::calculateProductOfTop3(std::vector<std::unordered_set<Coordinate> > & circuits) {
    int first = 0, second = 0, third = 0;

    for (const auto & circuit : circuits) {
        if (circuit.size() > first) {
            third = second;
            second = first;
            first = circuit.size();
        } else if (circuit.size() > second) {
            third = second;
            second = circuit.size();
        } else if (circuit.size() > third) {
            third = circuit.size();
        }
    }

    return first * second * third;
}
