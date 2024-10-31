#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <string>

class StringView {
   public:
    StringView() = default;
    StringView(const StringView& other) = default;
    StringView(const StringView&&) = delete;
    StringView& operator=(const StringView&) = default;
    StringView& operator=(const StringView&&) = delete;

    StringView(const std::string& str, size_t size) : data_(str.data()), size_(size) {
    }

    StringView(  // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
        const std::string& str)
        : data_(str.data()), size_(str.size()) {
    }

    StringView(const char* str)  // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
        : data_(str), size_(std::strlen(str)) {
    }

    StringView(const char* str, size_t size) : data_(str), size_(size) {
    }

    StringView(std::nullptr_t) = delete;

    template <std::random_access_iterator T>
    StringView(T first, T last) : data_(&*first), size_(std::distance(first, last)) {
    }

    char operator[](size_t index) const {
        return At(index);
    }

    [[nodiscard]] StringView Substr(
        size_t start = 0,                         // NOLINT(fuchsia-default-arguments-declarations)
        size_t size = std::string::npos) const {  // NOLINT(fuchsia-default-arguments-declarations)
        return {std::next(data_, static_cast<int64_t>(start)), std::min(size, size_ - start)};
    }

    [[nodiscard]] const char* Data() const {
        return data_;
    }

    [[nodiscard]] size_t Size() const {
        return size_;
    }

    [[nodiscard]] char At(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("StringView::operator[]");
        }
        return *std::next(data_, static_cast<int64_t>(index));
    }

    [[nodiscard]] bool Empty() const {
        return size_ == 0;
    }

    [[nodiscard]] char Front() const {
        return At(0);
    }

    [[nodiscard]] char Back() const {
        return At(size_ - 1);
    }

    ~StringView() = default;

   private:
    const char* data_ = nullptr;
    size_t size_ = 0;
};