#include "part2.h"

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    const long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 11, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    std::unordered_map<std::string, std::unordered_set<std::string> > nodes;

    for (auto &line: lines) {
        auto idx = line.find(':');

        auto from = line.substr(0, idx);
        auto to = line.substr(idx + 2);
        connectNodes(from, to, nodes);
    }


    std::unordered_map<std::string, long long> numPathsFromToOut;

    return countNumPathsFromToOut(nodes, false, false, "svr", numPathsFromToOut);
}

void Part2::connectNodes(const std::string &from, const std::string &str,
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


long long Part2::countNumPathsFromToOut(
    std::unordered_map<std::string, std::unordered_set<std::string> > &nodes,
    bool seenFft,
    bool seenDac,
    const std::string &from,
    std::unordered_map<std::string, long long> &numPathsFromToOut) {
    if (from == "fft") seenFft = true;
    if (from == "dac") seenDac = true;

    long long totalPaths = 0;
    auto key = makeKey(from, seenFft, seenDac);
    if (numPathsFromToOut.contains(key)) return numPathsFromToOut[key];
    if (nodes[from].contains("out") && seenFft && seenDac) {
        totalPaths += 1;
    }

    for (auto &to: nodes[from]) {
        if (to == "out") continue;
        totalPaths += countNumPathsFromToOut(nodes, seenFft, seenDac, to, numPathsFromToOut);
    }

    return numPathsFromToOut[key] = totalPaths;
}

std::string Part2::makeKey(const std::string& from, bool seenFft, bool seenDac) {
    return from + "_" + std::to_string(seenFft) + "_" +std::to_string(seenDac);
}
