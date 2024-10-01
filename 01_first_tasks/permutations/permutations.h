#pragma once

#include <cstddef>
#include <set>
#include <vector>

inline std::vector<std::vector<int>> Gen(size_t len, std::set<int>& exclude) {
    std::vector<std::vector<int>> result;
    if (exclude.size() == len) {
        return result;
    }
    for (int i = 0; i < static_cast<int>(len); i++) {
        if (exclude.contains(i)) {
            continue;
        }
        std::set excl(exclude);
        excl.insert(i);
        auto v = Gen(len, excl);
        for (auto vect : v) {
            std::vector vv(1, i);
            vv.insert(vv.end(), vect.begin(), vect.end());
            result.push_back(vv);
        }
        if (v.empty()) {
            result.push_back({i});
        }
    }
    return result;
}

inline std::vector<std::vector<int>> GeneratePermutations(size_t len) {
    std::set<int> s;
    return Gen(len, s);
}
