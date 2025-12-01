#include "../common/Utils.h"

int main() {
    auto lines = AoC::loadInput("input.txt");

    std::cout << "Read " << lines.size() << " lines from input." << std::endl;

    int clock = 50, ans = 0;
    for (std::string &line: lines) {
        std::cout << "Input " << clock << std::endl;

        if (line[0] == 'L') clock -= std::stoi(line.substr(1));
        else if (line[0] == 'R') clock += std::stoi(line.substr(1));
        std::cout << clock << " : " << ans << std::endl;

        ans += std::abs(clock / 100);
        clock %= 100;

        if (clock < 0) {
            ans++;
            clock = 100 - std::abs(clock);
        }
        std::cout << "Output " <<  clock << " : " << ans << std::endl;
    }
    std::cout << "Ans: " << ans << std::endl;

    return 0;
}
