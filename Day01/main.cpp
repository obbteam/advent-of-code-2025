#include "../common/Utils.h"
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    auto lines = AoC::loadInput("input.txt");

    int clock = 50, ans = 0;
    for (std::string &line: lines) {

        if (line[0] == 'L') clock -= std::stoi(line.substr(1));
        else if (line[0] == 'R') clock += std::stoi(line.substr(1));

        ans += std::abs(clock / 100);
        clock %= 100;

        if (clock < 0) {
            ans++;
            clock = 100 - std::abs(clock);
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 1, 2, ans, start, end));

    return 0;
}
