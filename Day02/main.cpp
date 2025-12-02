#include <unordered_set>

#include "../common/Utils.h"

long long parseInputAndSolve(const std::string &line);

long long solve(const std::string &left, const std::string &right);

std::string MakeDuplicate( const std::string& str, int x );

int main() {
    auto line = AoC::loadInput("input.txt");

    long long ans = parseInputAndSolve(line[0]);

    std::cout << "Ans: " << ans << std::endl;

    return 0;
}

long long solve(const std::string &left, const std::string &right) {
    long long ans = 0;
    std::unordered_set<long long> seen;
    for (long long i = stoll(left); i <= std::stoll(right); ++i) {
        std::string str = std::to_string(i);
        for (int j = 1; j <= str.length() / 2; ++j) {
            auto temp = MakeDuplicate(str.substr(0, j), str.length() / j);
            if (str == temp && !seen.contains(i)) {
                seen.insert(i);
                ans += i;
                std::cout << temp << std::endl;
            };
        }
    }
    return ans;
}

std::string MakeDuplicate( const std::string& str, int x )
{
    std::string newstr;
    newstr.reserve(str.length()*x); // prevents multiple reallocations

    for (int i = 0; i < x; ++i) {
        newstr += str;
    }

    return newstr;
}

long long parseInputAndSolve(const std::string &line) {
    std::vector<std::pair<int, int> > res;
    std::string left, right;
    bool r = false;
    long long ans = 0;

    for (const char &c: line) {
        if (c == ',') {
            ans += solve(left, right);
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
    ans += solve(left, right);

    return ans;
}
