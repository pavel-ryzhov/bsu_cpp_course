#pragma once

#include <cstddef>
#include <utility>

template <class Iterator>
class Sequence {
   public:
    Sequence(Iterator begin, Iterator end) : begin_{std::move(begin)}, end_{std::move(end)} {
    }

    [[nodiscard]] Iterator begin() const {  // NOLINT(readability-identifier-naming)
        return begin_;
    }

    [[nodiscard]] Iterator end() const {  // NOLINT(readability-identifier-naming)
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

class RangeIterator {
   public:
    RangeIterator(
        size_t from, size_t to, size_t step = 1)  // NOLINT(fuchsia-default-arguments-declarations)
        : from_{from}, to_{to}, step_{step} {
    }

    explicit RangeIterator(size_t to) : from_{0}, to_{to}, step_{1} {
    }

    RangeIterator& operator++() {
        from_ += step_;
        return *this;
    }

    auto operator*() const {
        return from_;
    }

    bool operator==(const RangeIterator& rhs) const = default;

   private:
    size_t from_, to_, step_;
};

template <class Iterator1, class Iterator2>
class ZipIterator {
   public:
    ZipIterator(
        Iterator1 first_begin, Iterator1 first_end, Iterator2 second_begin, Iterator2 second_end)
        : first_begin_{std::move(first_begin)}
        , first_end_{std::move(first_end)}
        , second_begin_{std::move(second_begin)}
        , second_end_{std::move(second_end)} {
        if (first_begin_ == first_end_) {
            second_it_ = second_end_;
        } else if (second_begin_ == second_end_) {
            first_it_ = first_end_;
        }
    }

    ZipIterator& operator++() {
        if (++first_it_ == first_end_) {
            second_it_ = second_end_;
        } else if (++second_it_ == second_end_) {
            first_it_ = first_end_;
        }
        return *this;
    }

    auto operator*() const {
        return std::pair{*first_it_, *second_it_};
    }

    bool operator==(const ZipIterator& rhs) const {
        return first_it_ == rhs.first_it_ && second_it_ == rhs.second_it_;
    }

   private:
    Iterator1 first_begin_, first_end_;
    Iterator2 second_begin_, second_end_;
    Iterator1 first_it_ = first_begin_;
    Iterator2 second_it_ = second_begin_;
};

template <class Iterator>
class GroupIterator {
   public:
    GroupIterator(Iterator begin, Iterator end)
        : begin_{std::move(begin)}, it_begin_{begin_}, it_end_{begin_}, end_{std::move(end)} {
        CalculateItEnd();
    }

    GroupIterator& operator++() {
        it_begin_ = it_end_;
        CalculateItEnd();
        return *this;
    }

    auto operator*() const {
        return Sequence{it_begin_, it_end_};
    }

    bool operator==(const GroupIterator& rhs) const {
        return it_begin_ == rhs.it_begin_ && it_end_ == rhs.it_end_;
    }

   private:
    Iterator begin_, it_begin_, it_end_, end_;

    void CalculateItEnd() {
        while (it_end_ != end_ && *it_begin_ == *it_end_) {
            ++it_end_;
        }
    }
};

auto Repeat(const auto& sequence, size_t n) {
    auto begin = sequence.begin();
    auto end = sequence.end();
    if (n && (begin != end)) {
        return Sequence{RepeatIterator{begin, end}, RepeatIterator{begin, end, n}};
    }
    return Sequence{RepeatIterator{end, end}, RepeatIterator{end, end}};
}

inline auto Range(
    size_t from, size_t to, size_t step = 1) {  // NOLINT(fuchsia-default-arguments-declarations)
    if ((to - from) % step != 0) {
        to = from + ((to - from) / step + 1) * step;
    }
    return Sequence{RangeIterator{from, to, step}, RangeIterator{to, to, step}};
}

inline auto Range(size_t to) {
    return Range(0, to, 1);
}

auto Zip(const auto& sequence1, const auto& sequence2) {
    auto begin1 = sequence1.begin();
    auto end1 = sequence1.end();
    auto begin2 = sequence2.begin();
    auto end2 = sequence2.end();
    return Sequence{ZipIterator{begin1, end1, begin2, end2}, ZipIterator{end1, end1, end2, end2}};
}

auto Group(const auto& sequence) {
    return Sequence{
      GroupIterator{sequence.begin(), sequence.end()},
      GroupIterator{sequence.end(), sequence.end()}};
}
