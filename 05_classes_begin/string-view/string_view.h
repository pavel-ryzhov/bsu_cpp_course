#pragma once

#include <string>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <cstddef>

// template<std::random_access_iterator T>
class StringView {
public:
    StringView() = default;
    StringView(const StringView&) = default;
    StringView(const StringView&&) = delete;
    StringView& operator=(const StringView&) = default;
    StringView& operator=(const StringView&&) = delete;
    StringView(const std::string& str, size_t size) : data_(str.data()), size_(size) {}
    StringView(const std::string& str) : data_(str.data()), size_(str.size()) {} // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    StringView(const char* str, size_t size) : data_(str), size_(size) {}
    StringView(const char* str) : data_(str), size_(std::strlen(str)) {} // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    StringView(std::nullptr_t) = delete;
    template<std::random_access_iterator T>
    StringView(T first, T last) : data_(first), size_(last - first) {}
    char operator[](size_t index) const {
        return At(index);
    }
    [[nodiscard]] std::string Substr(size_t start = 0, size_t size = std::string::npos) const {// NOLINT(fuchsia-default-arguments-declarations)
        return {data_ + start, size};
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
        return data_[index];
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
    // T data_ = nullptr;
    const char* data_ = nullptr;
    size_t size_ = 0;
};
