#pragma once

#include <string>
#include <utility>
#include <vector>

class FrozenMap {
   public:
    explicit FrozenMap(const std::vector<std::pair<std::string, std::string>>& items) {
    }

    bool Find(const std::string& key, std::string* value) const {
        return false;
    }
};
