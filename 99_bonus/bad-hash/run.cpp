#include "tools/util/util.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

bool CheckUserName(const std::string& user) {
    return std::ranges::all_of(
        user, [](char c) { return std::isalpha(c) != 0 || std::isdigit(c) != 0 || (c == '_'); });
}

bool GetLine(std::ifstream& in, std::string* line, size_t max_length) {
    line->clear();
    while (in && (line->size() <= max_length)) {
        auto symbol = in.get();
        if (symbol == '\n') {
            return true;
        }
        line->push_back(static_cast<char>(symbol));
    }
    return false;
}

std::vector<std::string> GetUsers(std::ifstream& in, size_t max_count) {
    std::vector<std::string> users;
    std::string cur_line;
    while (users.size() < max_count) {
        auto is_valid = GetLine(in, &cur_line, 15U);
        if (in.eof()) {
            break;
        }
        if (!is_valid) {
            std::cout << "Too long username " << cur_line << "\n";
            std::exit(0);  // NOLINT(concurrency-mt-unsafe)
        } else if (!CheckUserName(cur_line)) {
            std::cout << "Incorrect username " << cur_line << "\n";
            std::exit(0);  // NOLINT(concurrency-mt-unsafe)
        } else {
            users.push_back(cur_line);
        }
    }
    return users;
}

int main() {  // NOLINT(bugprone-exception-escape)
    std::ifstream in("99_bonus/bad-hash/input.txt");
    if (!in) {
        std::cout << "Bad file path\n";
        std::exit(0);  // NOLINT(concurrency-mt-unsafe)
    }
    std::random_device gen;
    if (gen.entropy() == 0.0) {
        std::cout << "Bad random device\n";
        std::exit(0);  // NOLINT(concurrency-mt-unsafe)
    }
    std::uniform_int_distribution dist{30'000, 1'000'000};

    std::unordered_set<std::string> users(dist(gen));
    auto users_list = GetUsers(in, 15'000);
    const Timer timer;

    for (auto& user : users_list) {
        users.insert(std::move(user));
    }

    auto [wall_time, cpu_time] = timer.GetTimes();
    auto spent = std::chrono::duration<double>{wall_time};
    std::cout << "Spent " << spent.count() << " seconds\n";

    if (wall_time > std::chrono::seconds{1}) {
        if (cpu_time < .98 * wall_time) {
            std::cout << "Sorry, but CI is laggy 😥\n";
            std::cout << "Try later...\n";
        } else {
            std::cout << "Shit happens\n";
            return 1;
        }
    }
}
