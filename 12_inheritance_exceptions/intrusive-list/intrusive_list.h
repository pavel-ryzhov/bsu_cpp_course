#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>

class ListHook {
   public:
    [[nodiscard]] bool IsLinked() const {
        return prev_ != this;
    }

    void Unlink() {
        prev_->next_ = next_;
        next_->prev_ = prev_;
        prev_ = this;
        next_ = this;
    }

    ListHook(const ListHook&) = delete;
    ListHook& operator=(const ListHook&) = delete;
    ListHook(ListHook&&) = delete;
    ListHook& operator=(ListHook&&) = delete;

   protected:
    ListHook() : prev_(this), next_(this) {
    }

    ~ListHook() {
        Unlink();
    }
    template <class T>
    friend class List;

   private:
    ListHook* prev_ = nullptr;
    ListHook* next_ = nullptr;

    static ListHook* New() {    // костыль
        return new ListHook();  // NOLINT(cppcoreguidelines-owning-memory)
    }
};

template <class T>
class List {
   public:
    class Iterator {
       public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(ListHook* node) : node_(node) {
        }

        Iterator() = default;

        Iterator& operator++() {
            node_ = node_->next_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++*this;
            return tmp;
        }

        Iterator& operator--() {
            node_ = node_->prev_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --*this;
            return tmp;
        }

        T& operator*() const {
            return *static_cast<T*>(node_);
        }

        T* operator->() const {
            return &*static_cast<T*>(node_);
        }

        bool operator==(const Iterator& other) const {
            return node_ == other.node_;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

       private:
        ListHook* node_ = nullptr;
    };

    List() : dummy_(new ListHook()) {
    }

    List(const List&) = delete;

    List(List&& other) noexcept : dummy_(std::exchange(other.dummy_, ListHook::New())) {
    }

    List& operator=(const List&) = delete;

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            this->~List();
            new (this) List(std::move(other));
        }
        return *this;
    }

    [[nodiscard]] bool IsEmpty() const {
        return !dummy_->IsLinked();
    }

    [[nodiscard]] size_t Size() const {
        return std::distance(Begin(), End());
    }

    void PushBack(T* elem) {
        LinkAfter(dummy_->prev_, elem);
    }

    void PushFront(T* elem) {
        LinkAfter(dummy_, elem);
    }

    [[nodiscard]] T& Front() {
        return *static_cast<T*>(dummy_->next_);
    }

    [[nodiscard]] const T& Front() const {
        return *static_cast<T*>(dummy_->next_);
    }

    [[nodiscard]] T& Back() {
        return *static_cast<T*>(dummy_->prev_);
    }

    [[nodiscard]] const T& Back() const {
        return *static_cast<T*>(dummy_->prev_);
    }

    void PopBack() {
        Back().Unlink();
    }

    void PopFront() {
        Front().Unlink();
    }

    [[nodiscard]] Iterator Begin() const {
        return Iterator(dummy_->next_);
    }

    [[nodiscard]] Iterator End() const {
        return Iterator(dummy_);
    }

    [[nodiscard]] Iterator IteratorTo(T* element) const {
        return Iterator(element);
    }

    ~List() {
        while (!IsEmpty()) {
            PopBack();
        }
        delete dummy_;
    }

   private:
    ListHook* dummy_ = nullptr;

    static void LinkAfter(ListHook* target, ListHook* after) {
        after->next_ = target->next_;
        target->next_->prev_ = after;
        after->prev_ = target;
        target->next_ = after;
    }
};

template <class T>
typename List<T>::Iterator begin(List<T>& list) {
    return list.Begin();
}

template <class T>
typename List<T>::Iterator end(List<T>& list) {
    return list.End();
}
