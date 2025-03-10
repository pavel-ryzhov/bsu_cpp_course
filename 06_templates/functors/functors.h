#pragma once

#include <algorithm>
#include <cstddef>

template <class Functor>
class ReverseUnaryFunctor {
   public:
    explicit ReverseUnaryFunctor(Functor functor) : functor_(functor) {
    }

    bool operator()(auto& arg) {
        return !functor_(arg);
    }

   private:
    Functor functor_;
};

template <class Functor>
class ReverseBinaryFunctor {
   public:
    explicit ReverseBinaryFunctor(Functor functor) : functor_(functor) {
    }

    bool operator()(auto& arg1, auto& arg2) {
        return !functor_(arg1, arg2);
    }

   private:
    Functor functor_;
};

auto MakeReverseUnaryFunctor(auto functor) {
    return ReverseUnaryFunctor{functor};
}

auto MakeReverseBinaryFunctor(auto functor) {
    return ReverseBinaryFunctor{functor};
}

template <class Iterator>
size_t ComparisonsCount(Iterator first, Iterator last) {
    size_t count = 0;
    std::sort(first, last, [&count](auto a, auto b) {
        count++;
        return a < b;
    });
    return count;
}
