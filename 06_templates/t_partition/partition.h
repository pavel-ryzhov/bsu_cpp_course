#pragma once

#include <utility>

template <class Iterator, class Predicate>
Iterator Partition(Iterator first, Iterator last, Predicate pred) {
    if (first == last) {
        return first;
    }
    auto right = --last;
    while (first != right) {
        while (first != right && pred(*first)) {
            ++first;
        }
        while (first != right && !pred(*right)) {
            --right;
        }
        std::swap(*first, *right);
    }
    if (pred(*first)) {
        ++first;
    }
    return first;
}
