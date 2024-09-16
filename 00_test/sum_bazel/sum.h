#pragma once

#include <cstdint>
#include <string>

inline int64_t Sum(int32_t a, int32_t b) {
    return static_cast<int64_t>(a) + b;
}

inline std::string BazelOutput() {
    // return output of "bazel query 'deps(//00_test/sum_bazel:all)' 2>/dev/null | grep -v "@" |
    // sort | md5sum | cut -c -15"
    return "8384be1f2a1f296";
}
