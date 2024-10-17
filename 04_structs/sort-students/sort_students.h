#pragma once

#include <algorithm>
#include <string>
#include <vector>

struct Student {
    std::string name, surname;
    int year, month, day;
};

enum class SortType { kByName, kByDate };

inline void SortStudents(std::vector<Student>* students, SortType sort_type) {
    std::sort(students->begin(), students->end(), [&](const Student& a, const Student& b) {
        switch (sort_type) {
            case SortType::kByName:
                return a.name < b.name;
            case SortType::kByDate:
                return a.year < b.year || a.month < b.month || a.day < b.day;
            default:
                return false;
        }
    });
}