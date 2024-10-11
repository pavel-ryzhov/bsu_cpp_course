#pragma once

#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

struct StudentName {
    std::string name, surname;
};

struct Date {
    int year, month, day;
};

inline std::map<std::string, std::vector<StudentName>> GetStudents(
    const std::vector<std::pair<std::string, int>>& universities_info,
    const std::vector<std::tuple<StudentName, Date, int, std::vector<std::string>>>&
        students_info) {
    throw std::runtime_error{"Not implemented!"};
}
