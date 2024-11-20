#pragma once

#include <cstddef>
#include <string>

class WeakPtr;

struct State {
    std::string* data = nullptr;
    size_t counter = 0;
    size_t all_counter = 0;
};

class SharedPtr {
   public:
    SharedPtr() : state_(new State(nullptr, 1, 1)) {
    }

    SharedPtr(const SharedPtr& other) : state_(other.state_) {
        ++state_->counter;  // NOLINT(clang-analyzer-core.uninitialized.Assign)
        ++state_->all_counter;
    }

    explicit SharedPtr(const WeakPtr& ptr);

    explicit SharedPtr(std::string* str) : state_(new State(str, 1, 1)) {
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            this->~SharedPtr();
            state_ = other.state_;
            ++state_->counter;
            ++state_->all_counter;
        }
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept : state_(other.state_) {
        other.state_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            this->~SharedPtr();
            state_ = other.state_;
            other.state_ = nullptr;
        }
        return *this;
    }

    std::string& operator*() const {
        return *state_->data;
    }

    std::string* operator->() const {
        return state_->data;
    }

    [[nodiscard]] std::string* Get() const {
        return state_->data;
    }

    void Reset(std::string* str) {
        *this = SharedPtr(str);
    }

    ~SharedPtr() {
        if (state_ != nullptr &&
            --state_->counter == 0) {  // NOLINT(clang-analyzer-core.uninitialized.Assign)
            delete state_->data;
            state_->data = nullptr;
        }
        if (state_ != nullptr && --state_->all_counter == 0) {
            delete state_;
            state_ = nullptr;
        }
    }

    friend class WeakPtr;

   private:
    State* state_ = nullptr;

    explicit SharedPtr(State* state) : state_(state) {
    }
};

class WeakPtr {
   public:
    WeakPtr() : state_(new State(nullptr, 0, 1)) {
    }

    explicit WeakPtr(const SharedPtr& shared) : state_(shared.state_) {
        ++state_->all_counter;  // NOLINT(clang-analyzer-core.uninitialized.Assign)
    }

    WeakPtr(const WeakPtr& other) : state_(other.state_) {
        ++state_->all_counter;
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            this->~WeakPtr();
            state_ = other.state_;
            ++state_->all_counter;
        }
        return *this;
    }

    WeakPtr(WeakPtr&& other) noexcept : state_(other.state_) {
        other.state_ = nullptr;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            this->~WeakPtr();
            state_ = other.state_;
            other.state_ = nullptr;
        }
        return *this;
    }

    std::string& operator*() const {
        return *state_->data;
    }

    std::string* operator->() const {
        return state_->data;
    }

    [[nodiscard]] std::string* Get() const {
        return state_->data;
    }

    [[nodiscard]] SharedPtr Lock() const {
        ++state_->counter;
        ++state_->all_counter;
        return SharedPtr{state_};
    }

    [[nodiscard]] bool IsExpired() const {
        return state_->data == nullptr;
    }

    ~WeakPtr() {
        if (state_ != nullptr &&
            --state_->all_counter == 0) {  // NOLINT(clang-analyzer-core.uninitialized.Assign)
            delete state_;
            state_ = nullptr;
        }
    }

    friend class SharedPtr;

   private:
    State* state_ = nullptr;
};

inline SharedPtr::SharedPtr(const WeakPtr& ptr) : state_(ptr.state_) {
    ++state_->counter;
    ++state_->all_counter;
}