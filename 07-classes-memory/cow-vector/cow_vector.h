#pragma once

#include <cstddef>
#include <string>
#include <vector>

struct State {
    int ref_count = 1;
    std::vector<std::string> data;
};

class COWVector {
   public:
    COWVector() : state_(new State()) {
    }

    ~COWVector() {
        if (state_ != nullptr && --state_->ref_count == 0) {
            delete state_;
        }
    }

    COWVector(COWVector&& other) noexcept : state_(other.state_) {
        other.state_ = nullptr;
        ++state_->ref_count;
        this->~COWVector();
    }

    COWVector& operator=(COWVector&& other) noexcept {
        if (this != &other) {
            this->~COWVector();
            state_ = other.state_;
            other.state_ = nullptr;
            ++state_->ref_count;
        }
        return *this;
    }

    COWVector(const COWVector& other) : state_(other.state_) {
        ++state_->ref_count;
    }

    COWVector& operator=(const COWVector& other) {
        if (this != &other) {
            this->~COWVector();
            state_ = other.state_;
            ++state_->ref_count;
        }
        return *this;
    }

    [[nodiscard]] size_t Size() const {
        return state_->data.size();
    }

    void Resize(size_t size) {
        if (size != state_->data.size()) {
            DeepCopy();
            state_->data.resize(size);
        }
    }

    [[nodiscard]] const std::string& Get(size_t at) const {
        return state_->data[at];
    }

    [[nodiscard]] const std::string& Back() const {
        return state_->data.back();
    }

    void PushBack(const std::string& value) {
        DeepCopy();
        state_->data.push_back(value);
    }

    void Set(size_t at, const std::string& value) {
        if (state_->data[at] != value) {
            DeepCopy();
            state_->data[at] = value;
        }
    }

   private:
    State* state_;

    void DeepCopy() {
        if (state_->ref_count > 1) {
            auto* new_state = new State();  // NOLINT(cppcoreguidelines-owning-memory)
            new_state->data = state_->data;
            --state_->ref_count;
            state_ = new_state;
        }
    }
};
