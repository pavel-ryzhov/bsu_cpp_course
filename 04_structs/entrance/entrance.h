#pragma once

#include <algorithm>
#include <cstddef>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

struct StudentName {
    std::string name, surname;
};

struct Date {
    int year = 0, month = 0, day = 0;
};

inline void SortStudents(
    std::vector<std::tuple<StudentName, Date, int, std::vector<std::string>>>& students) {
    std::ranges::sort(
        students, [&](const std::tuple<StudentName, Date, int, std::vector<std::string>>& a,
                      const std::tuple<StudentName, Date, int, std::vector<std::string>>& b) {
            const auto& [name1, date1, score1, universities1] = a;
            const auto& [name2, date2, score2, universities2] = b;
            return std::tie(score1, date1.year, date1.month, date1.day, name1.surname, name1.name) <
                   std::tie(score2, date2.year, date2.month, date2.day, name2.surname, name2.name);
        });
}

inline std::map<std::string, std::vector<StudentName>> GetStudents(
    const std::vector<std::pair<std::string, int>>& universities_info,
    const std::vector<std::tuple<StudentName, Date, int, std::vector<std::string>>>&
        students_info) {
    std::map universities0(universities_info.begin(), universities_info.end());
    std::vector students(students_info);
    std::map<std::string, std::vector<StudentName>> result;
    for (const auto& university : universities_info) {
        result[university.first] = std::vector<StudentName>();
    }
    SortStudents(students);
    for (const auto& [name, date, score, universities] : students) {
        for (const auto& university : universities) {
            if (result[university].size() < static_cast<size_t>(universities0[university])) {
                result[university].push_back(name);
                break;
            }
        }
    }
    return result;
}
