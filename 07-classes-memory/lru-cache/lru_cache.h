#pragma once

#include <cstddef>
#include <list>
#include <string>
#include <unordered_map>

class LruCache {
   public:
    explicit LruCache(size_t max_size) : max_size_(max_size) {
    }

    LruCache(const LruCache&) = delete;
    LruCache& operator=(const LruCache&) = delete;
    LruCache(LruCache&&) = delete;
    LruCache& operator=(LruCache&&) = delete;
    ~LruCache() = default;

    void Set(const std::string& key, const std::string& value) {
        const auto& it = values_.find(key);
        if (values_.size() >= max_size_) {
            if (it != values_.end()) {
                lru_list_.erase(iterators_[key]);
            } else {
                const auto& for_remove = lru_list_.back();
                values_.erase(for_remove);
                iterators_.erase(for_remove);
                lru_list_.pop_back();
            }
        } else {
            if (it != values_.end()) {
                lru_list_.erase(iterators_[key]);
            }
        }
        lru_list_.push_front(key);
        values_[key] = value;
        iterators_[key] = lru_list_.begin();
    }

    bool Get(const std::string& key, std::string* value) {
        if (const auto& it = values_.find(key); it != values_.end()) {
            *value = it->second;
            lru_list_.erase(iterators_[key]);
            lru_list_.push_front(key);
            return true;
        }
        return false;
    }

   private:
    std::unordered_map<std::string, std::string> values_;
    std::unordered_map<std::string, std::list<std::string>::iterator> iterators_;
    std::list<std::string> lru_list_;
    const size_t max_size_;
};
