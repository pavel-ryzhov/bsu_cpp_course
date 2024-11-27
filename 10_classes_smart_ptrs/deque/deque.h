#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <initializer_list>

constexpr size_t kChunkSize = 128;

template <class T, class V>
T* PointerArithmetics(T* pointer, V value) {
    return std::next(pointer, value);
}

class Deque {
   public:
    Deque() : chunks_(new int*[2]()), chunks_size_(2) {
    }

    Deque(const Deque& other)
        : chunks_(new int*[other.chunks_size_]())
        , chunks_size_(other.chunks_size_)
        , begin_(other.begin_)
        , end_(other.end_)
        , size_(other.size_) {
        CopyChunks(other.chunks_);
    }

    Deque(Deque&& other) noexcept
        : chunks_(other.chunks_)
        , chunks_size_(other.chunks_size_)
        , begin_(other.begin_)
        , end_(other.end_)
        , size_(other.size_) {
        other.chunks_ = nullptr;
    }

    explicit Deque(size_t size) {
        Resize(size);
    }

    Deque(std::initializer_list<int> list) {
        Resize(list.size());
        int64_t counter = 0;
        for (const auto it : list) {
            this->At(counter++) = it;
        }
    }

    Deque& operator=(const Deque& other) {
        if (this != &other) {
            this->~Deque();
            chunks_ = new int*[other.chunks_size_]();  // NOLINT(cppcoreguidelines-owning-memory)
            chunks_size_ = other.chunks_size_;
            begin_ = other.begin_;
            end_ = other.end_;
            size_ = other.size_;
            CopyChunks(other.chunks_);
        }
        return *this;
    }

    Deque& operator=(Deque&& other) noexcept {
        if (this != &other) {
            this->~Deque();
            chunks_ = other.chunks_;
            chunks_size_ = other.chunks_size_;
            begin_ = other.begin_;
            end_ = other.end_;
            size_ = other.size_;
            other.chunks_ = nullptr;
        }
        return *this;
    }

    ~Deque() {
        DeallocateAllChunks();
        delete[] chunks_;
        chunks_ = nullptr;
    }

    void Swap(Deque& other) {
        std::swap(chunks_, other.chunks_);
        std::swap(chunks_size_, other.chunks_size_);
        std::swap(begin_, other.begin_);
        std::swap(end_, other.end_);
        std::swap(size_, other.size_);
    }

    void PushBack(int value) {
        if (Size() + 1 > kChunkSize && GetChunk(static_cast<int64_t>(end_) + 1) ==
                                           GetChunk(static_cast<int64_t>(begin_))) [[unlikely]] {
            Reallocate();
        }
        AllocateChunkIfNecessary(GetChunk(static_cast<int64_t>(end_)));
        this->At(static_cast<int64_t>(end_)) = value;
        end_ = ValidIndex(static_cast<int64_t>(end_) + 1);
        ++size_;
    }

    void PopBack() {
        const int64_t index = static_cast<int64_t>(end_) - 1;
        end_ = ValidIndex(index);
        if (GetPosInChunk(static_cast<int64_t>(end_)) == 0) [[unlikely]] {
            DeallocateChunk(GetChunk(static_cast<int64_t>(end_)));
        }
        --size_;
    }

    void PushFront(int value) {
        if (Size() + 1 > kChunkSize && GetChunk(static_cast<int64_t>(begin_) - 1) ==
                                           GetChunk(static_cast<int64_t>(end_))) [[unlikely]] {
            Reallocate();
        }
        const int64_t index = static_cast<int64_t>(begin_) - 1;
        AllocateChunkIfNecessary(GetChunk(index));
        this->At(index) = value;
        begin_ = ValidIndex(index);
        ++size_;
    }

    void PopFront() {
        begin_ = ValidIndex(static_cast<int64_t>(begin_) + 1);
        if (GetPosInChunk(static_cast<int64_t>(begin_)) == 0) [[unlikely]] {
            DeallocateChunk(GetChunk(static_cast<int64_t>(begin_) - 1));
        }
        --size_;
    }

    int& operator[](size_t index) {
        // const int64_t i = static_cast<int64_t>(begin_) + index;
        const auto i = static_cast<int64_t>(begin_ + index);
        return *PointerArithmetics(*PointerArithmetics(chunks_, GetChunk(i)), GetPosInChunk(i));
    }

    const int& operator[](size_t index) const {
        // const int64_t i = static_cast<int64_t>(begin_) + index;
        const auto i = static_cast<int64_t>(begin_ + index);
        return *PointerArithmetics(*PointerArithmetics(chunks_, GetChunk(i)), GetPosInChunk(i));
    }

    [[nodiscard]] size_t Size() const {
        return size_;
        // return ValidIndex(static_cast<int64_t>(end_) - static_cast<int64_t>(begin_));
    }

    [[nodiscard]] size_t Capacity() const {
        return static_cast<size_t>(std::ceil(static_cast<double>(Size()) / kChunkSize)) *
               kChunkSize;
    }

    void Clear() {
        DeallocateAllChunks();
        begin_ = 0;
        end_ = 0;
        size_ = 0;
    }

   private:
    int** chunks_ = nullptr;
    size_t chunks_size_ = 0;
    size_t begin_ = 0;
    size_t end_ = 0;
    size_t size_ = 0;

    [[nodiscard]] int& At(int64_t index) {
        return *PointerArithmetics(
            *PointerArithmetics(chunks_, GetChunk(index)), GetPosInChunk(index));
    }

    [[nodiscard]] const int& At(int64_t index) const {
        return *PointerArithmetics(
            *PointerArithmetics(chunks_, GetChunk(index)), GetPosInChunk(index));
    }

    [[nodiscard]] size_t ValidIndex(int64_t index) const {
        return (index + MaxCapacity()) % MaxCapacity();
    }

    [[nodiscard]] size_t MaxCapacity() const {
        const auto a = chunks_size_ * kChunkSize;
        return a == 0 ? -1 : a;
    }

    void Resize(size_t size) {
        if (size > 0) {
            chunks_size_ = std::ceil(static_cast<double>(size + 1) / kChunkSize);
            chunks_ = new int*[chunks_size_]();    // NOLINT(cppcoreguidelines-owning-memory)
            for (size_t i = 0; i < chunks_size_; ++i) {
                *PointerArithmetics(chunks_, i) =  // NOLINT(cppcoreguidelines-owning-memory)
                    new int[kChunkSize]();
            }
            begin_ = 0;
            end_ = size;
            size_ = size;
        }
    }

    [[nodiscard]] size_t GetChunk(int64_t index) const {
        return ValidIndex(index) / kChunkSize;
    }

    [[nodiscard]] size_t GetPosInChunk(int64_t index) const {
        return ValidIndex(index) % kChunkSize;
    }

    void AllocateChunkIfNecessary(size_t pos) const {
        // NOLINTNEXTLINE(clang-analyzer-core.UndefinedBinaryOperatorResult)
        if (*PointerArithmetics(chunks_, pos) == nullptr) [[unlikely]] {
            *PointerArithmetics(chunks_, pos) =  // NOLINT(cppcoreguidelines-owning-memory)
                new int[kChunkSize];
        }
    }

    void DeallocateAllChunks() const {
        if (chunks_ != nullptr) {
            for (size_t i = 0; i < chunks_size_; ++i) {
                // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
                delete[] *PointerArithmetics(  // NOLINT(clang-analyzer-core.CallAndMessage)
                    chunks_, i);
                *PointerArithmetics(chunks_, i) = nullptr;
            }
        }
    }

    void DeallocateChunk(size_t pos) const {
        delete[] *PointerArithmetics(chunks_, pos);  // NOLINT(cppcoreguidelines-owning-memory)
        *PointerArithmetics(chunks_, pos) = nullptr;
    }

    void Reallocate() {
        int** new_chunks = new int*[chunks_size_ * 2]();  // NOLINT(cppcoreguidelines-owning-memory)
        int** a = std::copy(
            PointerArithmetics(chunks_, GetChunk(static_cast<int64_t>(begin_))),
            PointerArithmetics(chunks_, chunks_size_), new_chunks);
        if (GetChunk(static_cast<int64_t>(begin_)) != 0) {
            std::copy_n(chunks_, GetChunk(static_cast<int64_t>(begin_)), a);
        }
        delete[] chunks_;
        chunks_ = new_chunks;
        end_ = (chunks_size_ - 1) * kChunkSize + end_ % kChunkSize;
        begin_ %= kChunkSize;
        chunks_size_ <<= 1U;
    }

    void CopyChunks(int** from) const {
        for (size_t i = 0; i < chunks_size_; ++i) {
            // NOLINTNEXTLINE(clang-analyzer-core.UndefinedBinaryOperatorResult)
            if (*PointerArithmetics(from, i) != nullptr) {
                *PointerArithmetics(chunks_, i) =  // NOLINT(cppcoreguidelines-owning-memory)
                    new int[kChunkSize];
                std::copy_n(
                    *PointerArithmetics(from, i), kChunkSize, *PointerArithmetics(chunks_, i));
            }
        }
    }
};