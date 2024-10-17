#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct Student {

    Student() = default;

    Student(std::string name, std::string surname, int year, int month, int day): name_(std::move(name)), surname_(std::move(surname)), year_(year), month_(month), day_(day) {}

    [[nodiscard]] std::string Name() const {
        return name_;
    }

    [[nodiscard]] std::string Surname() const {
        return surname_;
    }

    [[nodiscard]] int Year() const {
        return year_;
    }

    [[nodiscard]] int Month() const {
        return month_;
    }

    [[nodiscard]] int Day() const {
        return day_;
    }

private:
    std::string name_, surname_;
    int year_ = 0, month_ = 0, day_ = 0;
};

enum class SortType : uint8_t { kByName, kByDate };

inline void SortStudents(std::vector<Student>* students, SortType sort_type) {
    std::sort(students->begin(), students->end(), [&](const Student& a, const Student& b) {
        switch (sort_type) {
            case SortType::kByName:
                return a.Name() < b.Name();
            case SortType::kByDate:
                return a.Year() < b.Year() || a.Month() < b.Month() || a.Day() < b.Day();
            default:
                return false;
        }
    });
}