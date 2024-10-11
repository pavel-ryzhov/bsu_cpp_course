#include "sort_students.h"

#include <catch2/catch_test_macros.hpp>
#include <vector>

TEST_CASE("Your test") {
    std::vector<Student> data;
    SortStudents(&data, SortType::kByDate);
}
