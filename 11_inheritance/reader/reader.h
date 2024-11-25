#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <span>
#include <string>
#include <utility>

class Reader {
   public:
    Reader() = default;
    Reader(const Reader&) = default;
    Reader(Reader&&) = default;
    Reader& operator=(const Reader&) = default;
    Reader& operator=(Reader&&) = default;
    virtual ~Reader() = default;

    // Читает не более чем @len байт из потока.
    // Помещает результат чтения в буфер @buf.
    // Возвращает сколько байт удалось прочитать.
    // Возвращаемое значение 0 означает конец потока.

    virtual size_t Read(char* buf, size_t len) = 0;
};

inline std::string ReadAll(Reader* reader) {
    constexpr auto kChunkSize = 128;

    std::string buf;
    std::array<char, kChunkSize> chunk{};
    while (true) {
        if (auto size = reader->Read(chunk.data(), kChunkSize)) {
            for (size_t ind = 0; ind < size; ++ind) {
                buf.push_back(chunk.at(ind));
            }
        } else {
            return buf;
        }
    }
}

class EndlessReader : public Reader {
   public:
    size_t Read(char* buf, size_t len) override {
        for (auto& c : std::span{buf, len}) {
            c = static_cast<char>(dist_(gen_));
        }
        return len;
    }

   private:
    std::mt19937 gen_{42};  // NOLINT(cert-msc32-c,cert-msc51-cpp)
    std::uniform_int_distribution<int> dist_{'a', 'z'};
};

class StringReader : public Reader {
   public:
    StringReader(StringReader&&) = delete;
    StringReader& operator=(const StringReader&) = delete;
    StringReader& operator=(StringReader&&) = delete;
    ~StringReader() override = default;

    explicit StringReader(std::string data) : data_{std::move(data)}, it_{data_.begin()} {
    }

    StringReader(const StringReader&) = delete;

    size_t Read(char* buf, size_t len) override {
        auto read_len = std::min<size_t>(len, data_.end() - it_);
        // Reader может вернуть менее @len байт
        read_len = std::min<size_t>(read_len, 100);
        it_ = std::ranges::copy_n(it_, static_cast<int32_t>(read_len), buf).in;
        return read_len;
    }

   private:
    const std::string data_;
    std::string::const_iterator it_;
};

class OddStringReader : public Reader {
   public:
    OddStringReader(OddStringReader&&) = delete;
    OddStringReader& operator=(const OddStringReader&) = delete;
    OddStringReader& operator=(OddStringReader&&) = delete;
    ~OddStringReader() override = default;

    explicit OddStringReader(std::string data) : data_{std::move(data)}, it_{data_.begin()} {
    }

    OddStringReader(const OddStringReader&) = delete;

    size_t Read(char* buf, size_t len) override {
        auto read_len = std::min<size_t>(len, data_.end() - it_);

        // Reader может вернуть менее @len байт
        read_len = std::min<size_t>(read_len, 5);
        it_ = std::ranges::copy_n(it_, static_cast<int32_t>(read_len), buf).in;
        return read_len;
    }

   private:
    const std::string data_;
    std::string::const_iterator it_;
};
