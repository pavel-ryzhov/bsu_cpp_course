#pragma once

#include <cstddef>
#include <utility>

template <class Iterator>
class Sequence {
   public:
    Sequence(Iterator begin, Iterator end) : begin_{std::move(begin)}, end_{std::move(end)} {
    }

    Iterator begin() const {  // NOLINT(readability-identifier-naming)
        return begin_;
    }

    Iterator end() const {  // NOLINT(readability-identifier-naming)
        return end_;
    }

   private:
    Iterator begin_, end_;
};

template <class Iterator>
class RepeatIterator {
   public:
    RepeatIterator(
        Iterator begin, Iterator end,
        size_t count = 0)  // NOLINT(fuchsia-default-arguments-declarations)
        : begin_{begin}, it_{begin}, end_{end}, count_{count} {
    }

    RepeatIterator& operator++() {
        if (!(++it_ != end_)) {
            ++count_;
            it_ = begin_;
        }
        return *this;
    }

    auto operator*() const {
        return *it_;
    }

    bool operator==(const RepeatIterator& rhs) const = default;

   private:
    Iterator begin_, it_, end_;
    size_t count_;
};

auto Repeat(const auto& sequence, size_t n) {
    auto begin = sequence.begin();
    auto end = sequence.end();
    if (n && (begin != end)) {
        return Sequence{RepeatIterator{begin, end}, RepeatIterator{begin, end, n}};
    }
    return Sequence{RepeatIterator{end, end}, RepeatIterator{end, end}};
}
