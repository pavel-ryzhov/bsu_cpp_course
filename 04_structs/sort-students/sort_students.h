#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

struct Student {
    std::string name, surname;
    int year = 0, month = 0, day = 0;
};

enum class SortType : uint8_t { kByName, kByDate };

inline void SortStudents(std::vector<Student>* students, SortType sort_type) {
    std::ranges::sort(students->begin(), students->end(), [&](const Student& a, const Student& b) {
        switch (sort_type) {
            case SortType::kByName:
                return a.name.compare(b.name) < 0 || a.surname.compare(b.surname) < 0;
            case SortType::kByDate:
                return a.year < b.year || a.month < b.month || a.day < b.day;
            default:
                return false;
        }
    });
}