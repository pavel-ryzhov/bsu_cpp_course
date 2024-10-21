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

inline bool CompareStudents(const Student& a, const Student& b);

inline bool CompareStudentsByName(const Student& a, const Student& b);

inline bool CompareStudents(const Student& a, const Student& b) {
    return a.year < b.year || a.month < b.month || a.day < b.day ||
           a.surname.compare(b.surname) < 0 || a.name.compare(b.name) < 0;
}

inline bool CompareStudentsByName(const Student& a, const Student& b) {
    return a.surname.compare(b.surname) < 0 || a.name.compare(b.name) < 0 || a.year < b.year ||
           a.month < b.month || a.day < b.day;
}

inline void SortStudents(std::vector<Student>* students, SortType sort_type) {
    std::sort(students->begin(), students->end(), [&](const Student& a, const Student& b) {
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