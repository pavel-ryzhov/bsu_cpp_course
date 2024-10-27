#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

class FrozenMap {
   public:
    explicit FrozenMap(const std::vector<std::pair<std::string, std::string>>& items) {
        items_.reserve(items.size());
        items_.insert(items_.end(), items.begin(), items.end());
        std::sort(
            items_.begin(), items_.end(),
            [](const std::pair<std::string, std::string>& a,
               const std::pair<std::string, std::string>& b) { return a.first < b.first; });
    }

    bool Find(const std::string& key, std::string* value) const {
        const auto a = std::lower_bound(
            items_.begin(), items_.end(), std::pair(key, ""),
            [](const std::pair<std::string, std::string>& a,
               const std::pair<std::string, std::string>& b) { return a.first < b.first; });
        if (a == items_.end() || a->first != key) {
            return false;
        }
        *value = a->second;
        return true;
    }

   private:
    std::vector<std::pair<std::string, std::string>> items_;
};
