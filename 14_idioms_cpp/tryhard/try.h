#pragma once
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay,bugprone-throw-keyword-missing)

#include <utility>

namespace tag {

constexpr inline struct Exception {
} kEx;

}  // namespace tag

template <class T>
class Try;

template <>
class Try<void>;

template <class Function, class... Args>
auto TryRun(Function func, Args&&... args) {
    using ReturnType = decltype(func(std::forward<Args>(args)...));
}

// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay,bugprone-throw-keyword-missing)
