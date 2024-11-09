#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>

class Vector {
   public:
    Vector() = default;

    Vector(const Vector& other) {
        operator=(other);
    }

    Vector(const std::initializer_list<int> list) : size_{list.size()} {
        Reserve(list.size());
        std::ranges::copy(list, begin());
    }

    Vector(Vector&& other) noexcept
        : size_{other.size_}, capacity_{other.capacity_}, begin_{other.begin_}, end_{other.end_} {
        other.begin_ = nullptr;
        other.end_ = nullptr;
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) [[unlikely]] {
            return *this;
        }
        size_ = other.size_;
        Reserve(other.Capacity());
        std::ranges::copy(other, begin());
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) [[unlikely]] {
            return *this;
        }
        this->~Vector();
        begin_ = other.begin_;
        end_ = other.end_;
        other.begin_ = nullptr;
        other.end_ = nullptr;
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;
    }

    ~Vector() {
        delete[] begin_;
        begin_ = nullptr;
        end_ = nullptr;
    }

    explicit Vector(size_t size) : size_{size} {
        Allocate(size);
    }

    int operator[](size_t index) const {
        return *GetPointer(index);
    }

    int& operator[](size_t index) {
        return *GetPointer(index);
    }

    void PushBack(int value) {
        if (capacity_ == 0) [[unlikely]] {
            Allocate(1);
        } else if (size_ == capacity_) [[unlikely]] {
            Allocate(capacity_ * 2);
        }
        (*this)[size_++] = value;
        end_ = std::next(end_);
    }

    void PopBack() {
        if (size_ == 0) [[unlikely]] {
            return;
        }
        --size_;
        end_ = std::prev(end_);
    }

    void Clear() {
        size_ = 0;
        end_ = begin_;
    }

    void Reserve(size_t capacity) {
        Allocate(capacity);
    }

    void Swap(Vector& other) {
        std::swap(begin_, other.begin_);
        std::swap(end_, other.end_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    [[nodiscard]] size_t Size() const {
        return size_;
    }

    [[nodiscard]] size_t Capacity() const {
        return capacity_;
    }

    class Iterator {
       public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = int;
        using difference_type = ptrdiff_t;
        using pointer = int*;
        using reference = int&;

        explicit Iterator(pointer data) : data_(data) {
        }

        Iterator() = default;

        Iterator& operator+=(const difference_type n) {
            data_ += n;
            return *this;
        }

        Iterator& operator-=(const difference_type n) {
            data_ -= n;
            return *this;
        }

        Iterator& operator++() {
            data_++;
            return *this;
        }

        Iterator operator++(int) {
            const Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            data_--;
            return *this;
        }

        Iterator operator--(int) {
            const Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator operator+(const difference_type n) const {
            return Iterator(data_ + n);
        }

        Iterator operator-(const difference_type n) const {
            return Iterator(data_ - n);
        }

        difference_type operator-(const Iterator& other) const {
            return data_ - other.data_;
        }

        reference operator[](const difference_type n) const {
            return *(data_ + n);
        }

        auto operator<=>(const Iterator&) const = default;

        reference operator*() const {
            if (data_ == nullptr) [[unlikely]] {
                static value_type zero = 0;
                return zero;
            }
            return *data_;
        }

        pointer operator->() const {
            return data_;
        }

       private:
        pointer data_ = nullptr;
    };

    [[nodiscard]] Iterator begin() const {
        return Iterator(begin_);
    }

    [[nodiscard]] Iterator end() const {
        return Iterator(end_);
    }

   private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    int* begin_ = nullptr;
    int* end_ = nullptr;

    void Allocate(size_t capacity) {
        if (capacity > capacity_) {
            auto* new_begin = new int[capacity]{};  // NOLINT(cppcoreguidelines-owning-memory)
            if (begin_ != nullptr) [[likely]] {
                std::copy(begin_, end_, new_begin);
                delete[] begin_;
            }
            capacity_ = capacity;
            begin_ = new_begin;
            end_ = GetPointer(size_);
        }
    }

    [[nodiscard]] int* GetPointer(size_t index) const {
        return std::next(begin_, static_cast<std::iterator_traits<int*>::difference_type>(index));
    }
};

inline Vector::Iterator operator+(
    const Vector::Iterator::difference_type n, const Vector::Iterator& it) {
    return it + n;
}