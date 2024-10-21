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

bool CompareStudents(const Student& a, const Student& b);

bool CompareStudentsByName(const Student& a, const Student& b);

inline bool Equal(const Student& a, const Student& b) {
    return a.name == b.name && a.surname == b.surname && a.year == b.year && a.month == b.month &&
           a.day == b.day;
}

inline bool CompareStudents(const Student& a, const Student& b) {
    return a.year < b.year || a.month < b.month || a.day < b.day || CompareStudentsByName(a, b);
}

inline bool CompareStudentsByName(const Student& a, const Student& b) {
    return a.surname.compare(b.surname) < 0 || a.name.compare(b.name) < 0 || CompareStudents(a, b);
}

inline void SortStudents(std::vector<Student>* students, SortType sort_type) {
    std::ranges::sort(students->begin(), students->end(), [&](const Student& a, const Student& b) {
        if (Equal(a, b)) {
            return false;
        }
        switch (sort_type) {
            case SortType::kByName:
                return CompareStudentsByName(a, b);
            case SortType::kByDate:
                return CompareStudents(a, b);
            default:
                return false;
        }
    });
}