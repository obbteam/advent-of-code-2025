#include "part2.h"

#include <unordered_set>

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 8, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    auto coordinates = getCoordinates(lines);

    return makeCircuits(coordinates);
}

std::vector<Coordinate> Part2::getCoordinates(const std::vector<std::string> &lines) {
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

long long Part2::makeCircuits(const std::vector<Coordinate> &coordinates) {
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
    // push the first one
    auto firstCandidate = shortestDistance.top();
    shortestDistance.pop();
    pushNewCircuit(circuits, firstCandidate);

    Coordinate finalFrom, finalTo;
    while (circuits.front().size() < coordinates.size()) {
        auto candidate = shortestDistance.top();
        shortestDistance.pop();
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
        pushToExistingCircuit(circuits, candidate, fromIdx, toIdx);
        finalFrom = candidate.from;
        finalTo = candidate.to;
    }

    // calculate final result
    return finalFrom.x * finalTo.x;
}

void Part2::pushNewCircuit(std::vector<std::unordered_set<Coordinate> > &circuits, CoordinatesDistance &c) {
    std::unordered_set<Coordinate> circuit;
    circuit.insert(c.from);
    circuit.insert(c.to);
    circuits.emplace_back(circuit);
}

void Part2::pushToExistingCircuit(
    std::vector<std::unordered_set<Coordinate> > &circuits,
    const CoordinatesDistance &c,
    const int& fromIdx,
    const int& toIdx
) {
    if (fromIdx != -1 && toIdx == -1)
        circuits[fromIdx].insert(c.to);
    else if (toIdx != -1 && fromIdx == -1) {
        circuits[toIdx].insert(c.from);
    } else if (fromIdx == toIdx && fromIdx == -1) {
        // nothing found
        std::unordered_set<Coordinate> circuit;
        circuit.insert(c.from);
        circuit.insert(c.to);
        circuits.emplace_back(circuit);
    } else if (fromIdx != toIdx) {
        // merge 2 circuits
        auto toRemove = circuits[toIdx];
        circuits[fromIdx].insert(toRemove.begin(), toRemove.end());
        circuits.erase(circuits.begin() + toIdx);
    }
}
