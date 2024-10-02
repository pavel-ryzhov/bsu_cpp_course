#pragma once

#include <vector>

inline std::vector<int> Unique(const std::vector<int>& data) {
    std::vector<int> result;
    if (data.empty()) {
        return result;
    }
    int previous = data[0] - 1;
    for (const int d : data) {
        if (d != previous) {
            result.push_back(d);
            previous = d;
        }
    }
    return result;
}
