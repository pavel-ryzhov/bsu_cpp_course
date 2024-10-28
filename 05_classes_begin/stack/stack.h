#pragma once

#include <cstddef>
#include <vector>

class Stack {
   public:
    void Push(int x) {
        vector_.push_back(x);
    }

    bool Pop() {
        if (vector_.empty()) {
            return false;
        }
        vector_.pop_back();
        return true;
    }

    [[nodiscard]] int Top() const {
        return vector_.back();
    }

    [[nodiscard]] bool Empty() const {
        return vector_.empty();
    }

    [[nodiscard]] size_t Size() const {
        return vector_.size();
    }

   private:
    std::vector<int> vector_;
};
