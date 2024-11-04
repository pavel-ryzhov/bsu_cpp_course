#pragma once

#include <cstddef>
#include <vector>

struct Sum {
    int operator()(const int a, const int b) const {
        return a + b;
    }
};

struct Prod {
    int operator()(const int a, const int b) const {
        return a * b;
    }
};

struct Concat {
    template <class T>
    std::vector<T> operator()(const std::vector<T>& a, const std::vector<T>& b) const {
        std::vector<T> result;
        result.reserve(a.size() + b.size());
        result.insert(result.end(), a.begin(), a.end());
        result.insert(result.end(), b.begin(), b.end());
        return result;
    }
};

class Length {
   public:
    explicit Length(size_t* length) : length_(length) {
    }

    template <class T>
    const T& operator()(const T& a, const T& /*b*/) const {
        (*length_)++;
        return a;
    }

   private:
    size_t* length_;
};

template <class Iterator, class T, class BinaryOp>
T Fold(Iterator first, Iterator last, T init, BinaryOp func) {
    T arg = init;
    for (; first != last; ++first) {
        arg = func(arg, *first);
    }
    return arg;
}
