#pragma once

inline void Swap(int* a, int* b) {
    const int temp = *a;
    *a = *b;
    *b = temp;
}

inline void Sort3(int* a, int* b, int* c) {
    if (*c < *a) {
        Swap(a, c);
    }
    if (*c < *b) {
        Swap(b, c);
    }
    if (*b < *a) {
        Swap(a, b);
    }
}
