#pragma once

template <class Iterator>
Iterator LocalMax(Iterator first, Iterator last) {
    auto it = first;
    while (it != last) {
        bool left = it == first;
        if (!left) {
            left = *first < *it;
            ++first;
        }
        bool right = it == last;
        if (!right) {
            const auto& a = *it;
            ++it;
            right = a > *it;
        }
        if (left && right) {
            return it;
        }
    }
    return last;
}
