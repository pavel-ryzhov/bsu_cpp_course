#pragma once

#include <iterator>
#include <utility>
#include <vector>

template <class Iterator, class Predicate, class Functor>
void TransformIf(Iterator begin, Iterator end, Predicate p, Functor f) {
    std::vector<std::pair<Iterator, typename std::iterator_traits<Iterator>::value_type>> log;
    bool error = false;
    try {
        for (Iterator it = begin; it != end; ++it) {
            if (p(*it)) {
                try {
                    log.emplace_back(it, *it);
                } catch (...) {
                    error |= true;
                }
                f(*it);
            }
        }
    } catch (...) {
        if (!error) {
            for (const auto& [it, value] : log) {
                *it = value;
            }
        }
        throw;
    }
}