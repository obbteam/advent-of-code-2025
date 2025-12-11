#include "part1.h"

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    const long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 11, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
    std::unordered_map<std::string, std::unordered_set<std::string>> nodes;

    for (auto &line: lines) {
        auto idx = line.find(':');

        auto from = line.substr(0, idx);
        auto to = line.substr(idx + 2);
        connectNodes(from, to, nodes);
    }


    std::unordered_map<std::string, long long> numPathsFromToOut;
    return countNumPathsFromToOut(nodes, "you", numPathsFromToOut);
}

void Part1::connectNodes(const std::string &from, const std::string &str,
                         std::unordered_map<std::string, std::unordered_set<std::string> > &nodes) {
    std::string cur;
    for (auto &c: str) {
        if (c == ' ') {
            if (!cur.empty())
                nodes[from].insert(cur);
            cur.clear();
            continue;
        }
        cur += c;
    }
    if (!cur.empty())
        nodes[from].insert(cur);
}


long long Part1::countNumPathsFromToOut(
    std::unordered_map<std::string, std::unordered_set<std::string> > &nodes,
    const std::string& from,
    std::unordered_map<std::string, long long> &numPathsFromToOut) {
    if (numPathsFromToOut.contains(from)) return numPathsFromToOut[from];
    if (nodes[from].contains("out")) return numPathsFromToOut[from] = 1;

    for (auto &to: nodes[from]) {
        numPathsFromToOut[to] = countNumPathsFromToOut(nodes, to, numPathsFromToOut);
        numPathsFromToOut[from] += numPathsFromToOut[to];
    }

    return numPathsFromToOut[from];
}
