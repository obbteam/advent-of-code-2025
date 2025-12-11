//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART2_H
#define ADVENT_OF_CODE_2025_PART2_H
#include <unordered_set>
#include <unordered_map>
#include <vector>


class Part2 {
public:
    void solve();

private:
    static long long parseAndSolve(std::vector<std::string> &lines);

    static void connectNodes(const std::string &from, const std::string &str,
                             std::unordered_map<std::string, std::unordered_set<std::string> > &nodes);

    static long long countNumPathsFromToOut(
        std::unordered_map<std::string, std::unordered_set<std::string> > &nodes,
        bool seenFft,
        bool seenDac,
        const std::string &from,
        std::unordered_map<std::string, long long> &numPathsFromToOut
    );

    static std::string makeKey(const std::string& from, bool seenFft, bool seenDac);
};


#endif //ADVENT_OF_CODE_2025_PART2_H
