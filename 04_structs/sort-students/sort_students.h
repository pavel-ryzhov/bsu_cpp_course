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

inline bool CompareStudents(const Student& a, const Student& b) {
    if (a.year != b.year) {
        return a.year < b.year;
    }
    if (a.month != b.month) {
        return a.month < b.month;
    }
    if (a.day != b.day) {
        return a.day < b.day;
    }
    if (a.surname != b.surname) {
        return a.surname < b.surname;
    }
    return a.name < b.name;
}

inline bool CompareStudentsByName(const Student& a, const Student& b) {
    if (a.surname != b.surname) {
        return a.surname < b.surname;
    }
    if (a.name != b.name) {
        return a.name < b.name;
    }
    if (a.year != b.year) {
        return a.year < b.year;
    }
    if (a.month != b.month) {
        return a.month < b.month;
    }
    return a.day < b.day;
}

inline void SortStudents(std::vector<Student>* students, SortType sort_type) {
    std::ranges::sort(*students, [&](const Student& a, const Student& b) {
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