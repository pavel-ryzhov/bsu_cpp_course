#pragma once

#include <cstddef>
#include <utility>
#include <vector>

inline void Rotate(std::vector<int>& nums) {
    const int t = nums[0];
    for (size_t i = 0; i < nums.size() - 1; i++) {
        std::swap(nums[i], nums[i + 1]);
    }
    nums.back() = t;
}

inline void Rotate(std::vector<int>& array, int n) {
    for (int i = 0; i < n; i++) {
        Rotate(array);
    }
}