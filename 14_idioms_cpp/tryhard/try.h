#pragma once
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay,bugprone-throw-keyword-missing)

#include <cstdint>
#include <exception>
#include <stdexcept>
#include <system_error>
#include <utility>
#include <variant>

namespace tag {

constexpr inline struct Exception {
} kEx;

}  // namespace tag

enum IndexType : uint8_t { empty, exception, value };

template <class T>
class Try {
   public:
    Try() = default;

    explicit Try(const T& value) : data_(std::in_place_index<IndexType::value>, value) {
    }

    explicit Try(T&& value) : data_(std::in_place_index<IndexType::value>, std::move(value)) {
    }

    template <class E>
    Try(tag::Exception /*tag*/, E&& exception)
        : data_(
              std::in_place_index<IndexType::exception>,
              std::make_exception_ptr(std::forward<E>(exception))) {
    }

    Try(tag::Exception /*tag*/, std::exception_ptr exception)
        : data_(std::in_place_index<IndexType::exception>, exception) {
    }

    Try(const Try&) = delete;
    Try(Try&&) = delete;
    Try& operator=(const Try&) = delete;
    Try& operator=(Try&&) = delete;
    ~Try() = default;

    [[nodiscard]] const T& Value() const {
        switch (data_.index()) {
            case value:
                return std::get<value>(data_);
            case exception:
                std::rethrow_exception(std::get<exception>(data_));
            default:
                throw std::runtime_error("Object is empty");
        }
    }

    void Throw() const {
        if (data_.index() == exception) {
            std::rethrow_exception(std::get<exception>(data_));
        }
        throw std::runtime_error("No exception");
    }

    [[nodiscard]] bool IsFailed() const {
        return data_.index() == exception;
    }

   private:
    std::variant<std::monostate, std::exception_ptr, T> data_;
};

template <>
class Try<void> {
   public:
    Try() = default;

    template <class E>
    Try(tag::Exception /*tag*/, E&& exception)
        : data_(
              std::in_place_index<IndexType::exception>,
              std::make_exception_ptr(std::forward<E>(exception))) {
    }

    Try(tag::Exception /*tag*/, std::exception_ptr exception)
        : data_(std::in_place_index<IndexType::exception>, exception) {
    }

    Try(const Try&) = delete;
    Try(Try&&) = delete;
    Try& operator=(const Try&) = delete;
    Try& operator=(Try&&) = delete;
    ~Try() = default;

    void Throw() const {
        if (data_.index() == exception) {
            std::rethrow_exception(std::get<exception>(data_));
        }
        throw std::runtime_error("No exception");
    }

    [[nodiscard]] bool IsFailed() const {
        return data_.index() == exception;
    }

   private:
    std::variant<std::monostate, std::exception_ptr> data_;
};

template <class Function, class... Args>
auto TryRun(Function func, Args&&... args) {
    using ReturnType = decltype(func(std::forward<Args>(args)...));
    try {
        if constexpr (std::is_void_v<ReturnType>) {
            func(std::forward<Args>(args)...);
            return Try<void>();
        } else {
            return Try<ReturnType>(func(std::forward<Args>(args)...));
        }
    } catch (const std::exception&) {
        return Try<ReturnType>(tag::kEx, std::current_exception());
    } catch (const char* e) {
        return Try<ReturnType>(tag::kEx, std::runtime_error(e));
    } catch (const int e) {
        return Try<ReturnType>(tag::kEx, std::system_error(e, std::generic_category()));
    } catch (...) {
        return Try<ReturnType>(tag::kEx, std::runtime_error("Unknown exception"));
    }
}

// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay,bugprone-throw-keyword-missing)
