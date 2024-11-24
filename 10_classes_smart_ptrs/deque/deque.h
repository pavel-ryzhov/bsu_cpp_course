#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <initializer_list>

constexpr size_t kChunkSize = 128;

class Deque {
   public:
    Deque() : chunks_(new int*[2]()), chunks_size_(2) {
    }
    Deque(const Deque& other) : chunks_(new int*[other.chunks_size_]()), chunks_size_(other.chunks_size_), begin_(other.begin_), end_(other.end_) {
        CopyChunks(other.chunks_);
    }
    Deque(Deque&& other) noexcept : chunks_(other.chunks_), chunks_size_(other.chunks_size_), begin_(other.begin_), end_(other.end_) {
        other.chunks_ = nullptr;
    }

    explicit Deque(size_t size) {
        Resize(size);
    }

    Deque(std::initializer_list<int> list) {
        Resize(list.size());
        auto it = list.begin();
        for (size_t i = 0; i < list.size(); ++i, ++it) {
            this->At(i) = *it;
        }
    }

    Deque& operator=(const Deque& other) {
        if (this != &other) {
            this->~Deque();
            chunks_ = new int*[other.chunks_size_]();
            chunks_size_ = other.chunks_size_;
            begin_ = other.begin_;
            end_ = other.end_;
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
    }

    void PushBack(int value) {
        if (Size() + 1 > kChunkSize && GetChunk(end_ + 1) == GetChunk(begin_)) [[unlikely]] {
            Reallocate();
        }
        AllocateChunkIfNecessary(GetChunk(end_));
        this->At(static_cast<int64_t>(end_)) = value;
        end_ = ValidIndex(end_ + 1);
    }

    void PopBack() {
        const int64_t index = static_cast<int64_t>(end_) - 1;
        end_ = ValidIndex(index);
        if (GetPosInChunk(end_) == 0) [[unlikely]] {
            DeallocateChunk(GetChunk(end_));
        }
        DeallocateLastChunkIfNecessary();
    }

    void PushFront(int value) {
        if (Size() + 1 > kChunkSize && GetChunk(static_cast<int64_t>(begin_) - 1) == GetChunk(end_)) [[unlikely]] {
            Reallocate();
        }
        const int64_t index = static_cast<int64_t>(begin_) - 1;
        AllocateChunkIfNecessary(GetChunk(index));
        this->At(index) = value;
        begin_ = ValidIndex(index);
    }

    void PopFront() {
        begin_ = ValidIndex(begin_ + 1);
        if (GetPosInChunk(begin_) == 0) [[unlikely]] {
            DeallocateChunk(GetChunk(static_cast<int64_t>(begin_) - 1));
        }
        DeallocateLastChunkIfNecessary();
    }

    int& operator[](int64_t index) {
        const int64_t i = static_cast<int64_t>(begin_) + index;
        return chunks_[GetChunk(i)][GetPosInChunk(i)];
    }

    const int& operator[](int64_t index) const {
        const int64_t i = static_cast<int64_t>(begin_) + index;
        return chunks_[GetChunk(i)][GetPosInChunk(i)];
    }

    [[nodiscard]] size_t Size() const {
        if (MaxCapacity() == 0) [[unlikely]] {
            return 0;
        }
        return ValidIndex(static_cast<int64_t>(end_) - begin_);
    }

    [[nodiscard]] size_t Capacity() const {
        return static_cast<size_t>(std::ceil(static_cast<double>(Size()) / kChunkSize)) * kChunkSize;
    }

    void Clear() {
        DeallocateAllChunks();
        begin_ = 0;
        end_ = 0;
    }

   private:
    int** chunks_ = nullptr;
    size_t chunks_size_ = 0;
    size_t begin_ = 0;
    size_t end_ = 0;

    [[nodiscard]] int& At(int64_t index) {
        return chunks_[GetChunk(index)][GetPosInChunk(index)];
    }

    [[nodiscard]] const int& At(int64_t index) const {
        return chunks_[GetChunk(index)][GetPosInChunk(index)];
    }

    [[nodiscard]] size_t ValidIndex(int64_t index) const {
        return (index + MaxCapacity()) % MaxCapacity();
    }

    [[nodiscard]] size_t MaxCapacity() const {
        return chunks_size_ * kChunkSize;
    }

    void Resize(size_t size) {
        if (size > 0) {
            chunks_size_ = std::ceil(static_cast<double>(size + 1) / kChunkSize);
            chunks_ = new int*[chunks_size_]();
            for (size_t i = 0; i < chunks_size_; ++i) {
                chunks_[i] = new int[kChunkSize]();
            }
            begin_ = 0;
            end_ = size;
        }
    }

    [[nodiscard]] size_t GetChunk(int64_t index) const {
        return ValidIndex(index) / kChunkSize;
    }

    [[nodiscard]] size_t GetPosInChunk(int64_t index) const {
        return ValidIndex(index) % kChunkSize;
    }

    void AllocateChunkIfNecessary(size_t pos) const {
        if (chunks_[pos] == nullptr) [[unlikely]] {
            chunks_[pos] = new int[kChunkSize];
        }
    }

    void DeallocateAllChunks() const {
        if (chunks_ != nullptr) {
            for (size_t i = 0; i < chunks_size_; ++i) {
                delete[] chunks_[i];
                chunks_[i] = nullptr;
            }
        }
    }

    void DeallocateChunk(size_t pos) const {
        delete[] chunks_[pos];
        chunks_[pos] = nullptr;
    }

    void DeallocateLastChunkIfNecessary() const {
        if (begin_ == end_) [[unlikely]] {
            DeallocateChunk(GetChunk(begin_));
        }
    }

    void Reallocate() {
        int** new_chunks = new int*[chunks_size_ * 2]();
        int** a = std::copy(chunks_ + GetChunk(begin_), chunks_ + chunks_size_, new_chunks);
        if (GetChunk(begin_) != 0) {
            std::copy_n(chunks_, GetChunk(begin_), a);
        }
        delete[] chunks_;
        chunks_ = new_chunks;
        end_ = (chunks_size_ - 1) * kChunkSize + end_ % kChunkSize;
        begin_ %= kChunkSize;
        chunks_size_ <<= 1;
    }

    void CopyChunks(int** from) const {
        for (size_t i = 0; i < chunks_size_; ++i) {
            if (from[i] != nullptr) {
                chunks_[i] = new int[kChunkSize];
                std::copy_n(from[i], kChunkSize, chunks_[i]);
            }
        }
    }
};