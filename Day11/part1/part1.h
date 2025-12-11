//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART1_H
#define ADVENT_OF_CODE_2025_PART1_H
#include <unordered_map>
#include <unordered_set>
#include <vector>


class Part1 {
public:
    void solve();

private:
    static long long parseAndSolve(std::vector<std::string> &lines);

    static void connectNodes(const std::string &from, const std::string &str,
                             std::unordered_map<std::string, std::unordered_set<std::string>> &nodes);

    static long long countNumPathsFromToOut(std::unordered_map<std::string, std::unordered_set<std::string>> &nodes,
                                     const std::string& from, std::unordered_map<std::string, long long> &numPathsFromToOut);
};


#endif //ADVENT_OF_CODE_2025_PART1_H
