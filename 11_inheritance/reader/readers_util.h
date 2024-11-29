#pragma once

#include "reader.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ios>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class LimitReader : public Reader {
   public:
    LimitReader(std::unique_ptr<Reader> reader, size_t limit)
        : reader_(std::move(reader)), limit_(limit) {
    }

    size_t Read(char* buf, size_t len) override {
        const auto read_len = std::min({len, limit_ - current_, limit_});
        const auto read = reader_->Read(buf, read_len);
        current_ += read;
        return read;
    }

   private:
    std::unique_ptr<Reader> reader_;
    size_t limit_;
    size_t current_ = 0;
};

class TeeReader : public Reader {
   public:
    explicit TeeReader(std::vector<std::unique_ptr<Reader>> readers)
        : readers_(std::move(readers)) {
    }

    size_t Read(char* buf, size_t len) override {
        size_t result = 0;
        while (readers_.size() > current_reader_) {
            if (len == result) {
                break;
            }
            const auto chunk_size = std::min(len, len - result);
            const auto read = readers_[current_reader_]->Read(buf, chunk_size);
            result += read;
            std::advance(buf, read);
            if (read == 0 && chunk_size != 0) {
                ++current_reader_;
            }
        }
        return result;
    }

   private:
    std::vector<std::unique_ptr<Reader>> readers_;
    size_t current_reader_ = 0;
};

static char HexToDec(const std::string& hex) {
    int result = 0;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> result;
    return static_cast<char>(result);
}

class HexDecodingReader : public Reader {
   public:
    explicit HexDecodingReader(std::unique_ptr<Reader> reader) : reader_(std::move(reader)) {
    }

    size_t Read(char* buf, size_t len) override {
        std::vector<char> buffer;
        buffer.resize(len);
        auto read_len = reader_->Read(buffer.data(), len);
        if (read_len % 2 == 1) {
            reader_->Read(std::next(buffer.data(), static_cast<int64_t>(read_len)), 1);
            ++read_len;
        }
        for (size_t i = 0; i < read_len / 2; ++i) {
            *buf = HexToDec(std::string(&buffer[i * 2], 2));
            std::advance(buf, 1);
        }
        return read_len / 2;
    }

   private:
    std::unique_ptr<Reader> reader_;
};
