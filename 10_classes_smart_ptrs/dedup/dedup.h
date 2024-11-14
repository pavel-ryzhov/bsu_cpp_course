#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> result;
    result.reserve(items.size());
    for (const auto& item : items) {
        result.push_back(std::make_unique<T>(*item));
    }
    return result;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::vector<std::shared_ptr<T>> result;
    std::unordered_map<T, std::shared_ptr<T>> map;
    result.reserve(items.size());
    for (const auto& item : items) {
        if (!map.contains(*item)) {
            map[*item] = std::make_shared<T>(*item);
        }
        result.push_back(map[*item]);
    }
    return result;
}
