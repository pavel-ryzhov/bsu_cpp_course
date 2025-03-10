// #pragma once
//
// template <class Iterator, class T>
// Iterator FindLast(Iterator first, Iterator last, const T& value) {
//     for (Iterator i = last; i != first;) {
//         --i;
//         if (*i ==
//             value) {  // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
//             return i;
//         }
//     }
//     return last;
// }
#pragma once

#include <vector>

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& value) {
    auto ans = last;
    for (auto i = first; i != last; ++i) {
        if (*i ==
            value) {  // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
            ans = i;
            }
    }
    return ans;
}

