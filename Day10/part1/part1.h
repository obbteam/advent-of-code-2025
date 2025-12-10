//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART1_H
#define ADVENT_OF_CODE_2025_PART1_H
#include <vector>

#include "LightState.h"


class Part1 {
public:
    void solve();

private:
    static long long parseAndSolve(std::vector<std::string> &lines);
    static LightState getLightDiagram(const std::string & str);
    static std::vector<LightState> getSchematics(const std::string & str);
    static int findMinButtons(const LightState& target, const std::vector<LightState>&  schematics);
};


#endif //ADVENT_OF_CODE_2025_PART1_H
