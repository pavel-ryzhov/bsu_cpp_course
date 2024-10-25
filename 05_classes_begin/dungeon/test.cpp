#include "dungeon.h"
#include "rogue.h"
#include "tools/util/util.h"

#include <array>
#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ranges>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

std::vector<std::unique_ptr<Room>> ReadDungeon(std::istream& in) {
    int num_rooms = 0;
    int num_open_doors = 0;
    int num_closed_doors = 0;
    int num_keys = 0;
    in >> num_rooms;

    std::vector<std::unique_ptr<Room>> dungeon(num_rooms);
    for (size_t i = 0; i < dungeon.size(); ++i) {
        dungeon[i] = std::make_unique<Room>(i + 1 == dungeon.size());
    }

    in >> num_keys;
    for (auto i = 0; i < num_keys; ++i) {
        int room = 0;
        std::string key;
        in >> room >> key;
        dungeon[room]->AddKey(key);
    }

    in >> num_open_doors;
    for (auto i = 0; i < num_open_doors; ++i) {
        int first_room = 0;
        int second_room = 0;
        in >> first_room >> second_room;
        dungeon[first_room]->AddDoor(dungeon[second_room].get());
    }

    in >> num_closed_doors;
    for (auto i = 0; i < num_closed_doors; ++i) {
        int first_room = 0;
        int second_room = 0;
        std::string key;
        in >> first_room >> second_room >> key;
        dungeon[first_room]->AddDoorWithKey(dungeon[second_room].get(), key);
    }

    return dungeon;
}

TEST_CASE("Signature") {
    INFO("Do not change FindFinalRoom signature");
    static_assert(std::is_same_v<decltype(&FindFinalRoom), const Room* (*)(const Room*)>);
}

void OneSimpleIter(
    size_t i, const std::vector<std::string>& test_dungeons, const std::vector<bool>& connected) {
    std::stringstream dungeon_stream{test_dungeons[i]};
    auto dungeon = ReadDungeon(dungeon_stream);
    const auto* exit_room = FindFinalRoom(dungeon[0].get());

    auto ok = connected[i] ? (exit_room == dungeon.back().get()) : exit_room == nullptr;
    if (!ok) {
        std::cerr << "Wrong answer. ";
        if (connected[i]) {
            std::cerr << "Expected room " << dungeon.size() << ", ";
        } else {
            std::cerr << "Expected nullptr, ";
        }

        for (const auto& room : dungeon) {
            if (room.get() == exit_room) {
                std::cerr << "Got room " << i << '\n';
            }
        }
        if (exit_room == nullptr) {
            std::cerr << "Got nullptr" << '\n';
        }

        std::cerr << "Test input:" << test_dungeons[i];
    }
    CHECK(ok);
}

TEST_CASE("SimpleDungeons") {
    const std::vector<std::string> test_dungeons = {
      R"EOF(
1
0
0
0
)EOF",
      R"EOF(
2
0
1
0 1
0
)EOF",
      R"EOF(
2
1
0 abc
0
1
0 1 abc
)EOF",
      R"EOF(
3
1
1 abc
1
0 1
1
0 2 abc
)EOF",
      R"EOF(
3
1
1 abc
1
0 1
1
1 2 abc
)EOF",
      R"EOF(
2
0
0
0
)EOF",
      R"EOF(
2
1
0 abc
0
1
0 1 bcd
)EOF",
      R"EOF(
2
1
1 abc
0
1
0 1 abc
)EOF",
      R"EOF(
4
0
3
0 1
1 2
2 1
0
)EOF",
    };

    const std::vector connected = {true, true, true, true, true, false, false, false, false};
    REQUIRE(connected.size() == test_dungeons.size());

    for (size_t i = 0; i < test_dungeons.size(); ++i) {
        OneSimpleIter(i, test_dungeons, connected);
    }
}

TEST_CASE("GeneratedDungeons") {
    constexpr auto kNumTests = 100;
    constexpr auto kNumRooms = 100;
    constexpr auto kNumDoors = 200;
    constexpr auto kNumClosedDoors = 100;

    auto seed = GENERATE(take(kNumTests, random(0U, 1'000'000'000U)));
    RandomGenerator rnd{seed};

    std::array<std::unique_ptr<Room>, kNumRooms> dungeon;
    for (auto& room : std::views::take(dungeon, kNumRooms - 1)) {
        room = std::make_unique<Room>(false);
    }
    dungeon.back() = std::make_unique<Room>(true);

    for (auto i = 0; i < kNumDoors; ++i) {
        auto from = rnd.GenInt(0, kNumRooms - 1);
        auto to = rnd.GenInt(0, kNumRooms - 1);
        dungeon.at(from)->AddDoor(dungeon.at(to).get());
    }

    for (auto i = 0; i < kNumClosedDoors; ++i) {
        auto from = rnd.GenInt(0, kNumRooms - 1);
        auto to = rnd.GenInt(0, kNumRooms - 1);
        auto key_location = rnd.GenInt(0, kNumRooms - 1);
        auto key = std::to_string(i);

        dungeon.at(key_location)->AddKey(key);
        dungeon.at(from)->AddDoorWithKey(dungeon.at(to).get(), key);
    }

    const auto* final_room = FindFinalRoom(dungeon.front().get());
    INFO("Wrong answer on generated dungeon");
    auto ok = (final_room == nullptr) || (final_room == dungeon.back().get());
    CHECK(ok);
}
