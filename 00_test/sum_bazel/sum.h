#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

inline int64_t Sum(int32_t a, int32_t b) {
    throw std::runtime_error("Not implemented");
}

inline std::string BazelOutput() {
    // return output of "bazel query 'deps(//00_test/sum_bazel:all)' 2>/dev/null | grep -v "@" | sort | md5sum | cut -c -15"
    throw std::runtime_error("Not implemented");
}
