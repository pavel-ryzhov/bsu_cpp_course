#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

template <class T>
concept NotAny = !std::same_as<std::remove_cvref_t<T>, class Any>;

class Any {
   public:
    struct InnerBase {
        InnerBase() = default;
        InnerBase(const InnerBase&) = default;
        InnerBase(InnerBase&&) = default;
        InnerBase& operator=(const InnerBase&) = default;
        InnerBase& operator=(InnerBase&&) = default;
        virtual ~InnerBase() = default;
        [[nodiscard]] virtual InnerBase* Clone() const = 0;
    };

    template <class T>
    struct Inner final : InnerBase {
        // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
        Inner(T value) : value_(std::forward<T>(value)) {
        }

        ~Inner() override = default;
        Inner(const Inner&) = default;
        Inner& operator=(const Inner&) = default;
        Inner(Inner&&) = default;
        Inner& operator=(Inner&&) = default;

        [[nodiscard]] InnerBase* Clone() const override {
            // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
            return new Inner(value_);
        }

        const T& operator*() const {
            return value_;
        }

        T& operator*() {
            return value_;
        }

       private:
        T value_;
    };

    Any() = default;

    template <NotAny T>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    Any(T&& value) : ptr_(new Inner<std::decay_t<T>>(std::forward<T>(value))) {
    }

    Any(const Any& other) : ptr_(other.ptr_ == nullptr ? nullptr : other.ptr_->Clone()) {
    }

    Any(Any&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {
    }

    Any& operator=(const Any& other) {
        if (this != &other) {
            Any tmp(other);
            std::swap(tmp.ptr_, this->ptr_);
        }
        return *this;
    }

    Any& operator=(Any&& other) noexcept {
        if (this != &other) {
            Any tmp(std::move(other));
            std::swap(tmp.ptr_, this->ptr_);
        }
        return *this;
    }

    ~Any() {
        delete ptr_;
        ptr_ = nullptr;
    }

    [[nodiscard]] bool Empty() const {
        return ptr_ == nullptr;
    }

    void Clear() {
        delete ptr_;
        ptr_ = nullptr;
    }

    void Swap(Any& other) {
        std::swap(ptr_, other.ptr_);
    }

    template <class T>
    [[nodiscard]] const T& GetValue() const {
        return *dynamic_cast<Inner<T>&>(*ptr_);
    }

   private:
    InnerBase* ptr_ = nullptr;
};
