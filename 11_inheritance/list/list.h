#pragma once

#include <cstddef>
#include <iterator>
#include <utility>

template <typename T>
class List {
   public:
    struct ListNode {
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
    };

    struct ListNodeWithValue : ListNode {
        explicit ListNodeWithValue(const T& value) : value_(value) {
        }

        explicit ListNodeWithValue(T&& value) : value_(std::move(value)) {
        }

        [[nodiscard]] const T& Value() const {
            return value_;
        }

        [[nodiscard]] T& Value() {
            return value_;
        }

       private:
        T value_;
    };

    class Iterator {
       public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(ListNode* node) : node_(node) {
        }

        Iterator() = default;

        Iterator& operator++() {
            node_ = node_->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++*this;
            return tmp;
        }

        Iterator& operator--() {
            node_ = node_->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --*this;
            return tmp;
        }

        T& operator*() const {
            return static_cast<ListNodeWithValue*>(node_)->Value();
        }

        T* operator->() const {
            return &*this;
        }

        bool operator==(const Iterator& other) const {
            return node_ == other.node_;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        [[nodiscard]] ListNode* Node() const {
            return node_;
        }

       private:
        ListNode* node_ = nullptr;
    };

    List() : head_(MakeHead()) {
    }

    List(const List& other) : head_(MakeHead()) {
        for (const auto& value : other) {
            PushBack(value);
        }
    }

    List(List&& other) noexcept : head_(std::exchange(other.head_, MakeHead())) {
    }

    List& operator=(const List& other) {
        if (this != &other) {
            this->~List();
            new (this) List(other);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            this->~List();
            new (this) List(std::move(other));
        }
        return *this;
    }

    ~List() {
        while (!IsEmpty()) {
            PopFront();
        }
        delete head_;
    }

    [[nodiscard]] bool IsEmpty() const {
        return head_->next == head_;
    }

    [[nodiscard]] size_t Size() const {
        return std::distance(Begin(), End());
    }

    void PushBack(const T& value) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        LinkAfter(head_->prev, new ListNodeWithValue(value));
    }

    void PushBack(T&& value) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        LinkAfter(head_->prev, new ListNodeWithValue(std::move(value)));
    }

    void PushFront(const T& value) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        LinkAfter(head_, new ListNodeWithValue(value));
    }

    void PushFront(T&& value) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        LinkAfter(head_, new ListNodeWithValue(std::move(value)));
    }

    T& Front() {
        return static_cast<ListNodeWithValue*>(head_->next)->Value();
    }

    [[nodiscard]] const T& Front() const {
        return static_cast<ListNodeWithValue*>(head_->next)->Value();
    }

    T& Back() {
        return static_cast<ListNodeWithValue*>(head_->prev)->Value();
    }

    [[nodiscard]] const T& Back() const {
        return static_cast<ListNodeWithValue*>(head_->prev)->Value();
    }

    void PopBack() {
        Unlink(head_->prev);
    }

    void PopFront() {
        Unlink(head_->next);
    }

    void Erase(Iterator it) {
        Unlink(it.Node());
    }

    [[nodiscard]] Iterator Begin() const {
        return Iterator(head_->next);
    }

    [[nodiscard]] Iterator End() const {
        return Iterator(head_);
    }

   private:
    ListNode* head_ = nullptr;

    static void Unlink(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        delete static_cast<ListNodeWithValue*>(node);
    }

    static void LinkAfter(ListNode* target, ListNode* after) {
        after->next = target->next;
        target->next->prev = after;
        after->prev = target;
        target->next = after;
    }

    static ListNode* MakeHead() {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        auto* result = new ListNode();
        result->next = result;
        result->prev = result;
        return result;
    }
};

template <typename T>
typename List<T>::Iterator begin(const List<T>& list) {
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(const List<T>& list) {
    return list.End();
}

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {
    return list.End();
}