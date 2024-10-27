#pragma once

#include "dungeon.h"

#include <cstddef>
#include <set>
#include <string>
#include <vector>

inline void ProcessDoor(
    const Door* door, std::vector<const Room*>& rooms, std::set<const Room*>& visited_rooms) {
    const auto* room = door->GoThrough();
    if (visited_rooms.find(room) == visited_rooms.end()) {
        rooms.push_back(room);
    }
}

inline const Room* FindFinalRoom(const Room* starting_room) {
    std::vector rooms = {starting_room};
    std::set<const Room*> visited_rooms;
    std::set<std::string> keys;
    std::set<Door*> doors;
    while (!rooms.empty()) {
        for (size_t i = rooms.size() - 1; i + 1 > 0; i--) {
            const auto* room = rooms[i];
            if (room->IsFinal()) {
                return room;
            }
            for (size_t j = 0; j < room->NumKeys(); j++) {
                keys.insert(room->GetKey(j));
            }
            for (size_t j = 0; j < room->NumDoors(); j++) {
                doors.insert(room->GetDoor(j));
            }
            visited_rooms.insert(room);
            rooms.pop_back();
        }
        for (auto* door : doors) {
            if (door->IsOpen()) {
                ProcessDoor(door, rooms, visited_rooms);
                continue;
            }
            for (const auto& key : keys) {
                if (door->TryOpen(key)) {
                    ProcessDoor(door, rooms, visited_rooms);
                    break;
                }
            }
        }
    }
    return nullptr;
}
