//
// Created by Obidkhon Akhmadkhonov on 10/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_LIGHTSTATE_H
#define ADVENT_OF_CODE_2025_LIGHTSTATE_H
#include <unordered_set>

struct LightState {
    std::unordered_set<int> switches;

    LightState() = default;
    LightState(std::unordered_set<int> s) : switches(std::move(s)) {}

    bool operator==(const LightState& other) const = default;

    LightState operator-(const LightState &other) const {
        std::unordered_set<int> result;

        for (const auto&n : switches) {
            if (!other.switches.contains(n))
                result.insert(n);
        }

        for (const auto&n : other.switches) {
            if (!switches.contains(n))
                result.insert(n);
        }

        return LightState(std::move(result));
    }
};


namespace std {
    template <>
    struct hash<LightState> {
        size_t operator()(const LightState &l) const {
            size_t final_hash = 0;

            for (const int& num : l.switches) {
                size_t h = std::hash<int>{}(num);
                final_hash += h;
            }

            return final_hash;
        }
    };
}


#endif //ADVENT_OF_CODE_2025_LIGHTSTATE_H