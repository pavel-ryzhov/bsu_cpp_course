#pragma once

#include <array>
#include <cstdint>
#include <queue>

enum class Winner : uint8_t { kFirst, kSecond, kNone };

struct GameResult {
    Winner winner;
    int turn;
};

inline bool CompareCards(int a, int b) {
    if (a == 0 && b == 11) [[unlikely]] {
        return true;
    }
    if (b == 0 && a == 11) [[unlikely]] {
        return false;
    }
    return a > b;
}

inline GameResult SimulateWarGame(
    const std::array<int, 6>& first_deck, const std::array<int, 6>& second_deck) {
    std::queue<int> deck1;
    std::queue<int> deck2;
    for (int i = 0; i < 6; i++) {
        deck1.push(first_deck.at(i));
        deck2.push(second_deck.at(i));
    }
    int c = 0;
    for (; !deck1.empty() && !deck2.empty() && c < 1'000'000; c++) {
        const int first = deck1.front();
        const int second = deck2.front();
        deck1.pop();
        deck2.pop();
        if (CompareCards(first, second)) {
            deck1.push(first);
            deck1.push(second);
        } else {
            deck2.push(first);
            deck2.push(second);
        }
    }
    if (deck1.empty()) {
        return GameResult{Winner::kSecond, c};
    }
    if (deck2.empty()) {
        return GameResult{Winner::kFirst, c};
    }
    return GameResult{Winner::kNone};
}