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
        const auto& a = *it;
        bool right = ++it == last;
        if (!right) {
            right = a > *it;
        }
        if (left && right) {
            --it;
            return it;
        }
    }
    return last;
}
