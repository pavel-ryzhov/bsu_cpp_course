#pragma once

#include <cstddef>
#include <vector>

class RingBuffer {
   public:
    explicit RingBuffer(size_t capacity) : capacity_(capacity) {
        data_.resize(capacity);
    }

    [[nodiscard]] size_t Size() const {
        return size_;
    }

    [[nodiscard]] bool Empty() const {
        return size_ == 0;
    }

    bool TryPush(int element) {
        if (size_ == capacity_) {
            return false;
        }
        data_[begin_] = element;
        size_++;
        begin_ + 1 < capacity_ ? begin_++ : begin_ = 0;
        return true;
    }

    bool TryPop(int* element) {
        if (size_ == 0) {
            return false;
        }
        *element = data_[end_];
        data_[end_] = 0;
        size_--;
        end_ + 1 < capacity_ ? end_++ : end_ = 0;
        return true;
    }

   private:
    size_t size_{0};
    size_t capacity_;
    size_t begin_{0};
    size_t end_{0};
    std::vector<int> data_;
};