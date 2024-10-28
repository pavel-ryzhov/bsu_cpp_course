#pragma once

#include <cstddef>
#include <vector>

class Stack {
   public:
    void Push(int x) {
        stack_.push_back(x);
    }

    bool Pop() {
        if (stack_.empty()) {
            return false;
        }
        stack_.pop_back();
        return true;
    }

    [[nodiscard]] int Top() const {
        return stack_.back();
    }

    [[nodiscard]] bool Empty() const {
        return stack_.empty();
    }

    [[nodiscard]] size_t Size() const {
        return stack_.size();
    }

   private:
    std::vector<int> stack_;
};
