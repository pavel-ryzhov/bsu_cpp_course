#pragma once

#include <stdexcept>
#include <string>
#include <vector>

struct Student {
    std::string name, surname;
    int year, month, day;
};

enum class SortType { kByName, kByDate };

inline void SortStudents(std::vector<Student>* students, SortType sort_type) {
    throw std::runtime_error{"Not implemented!"};
}
