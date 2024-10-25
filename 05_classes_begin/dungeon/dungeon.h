#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Room;

class Door {
   public:
    [[nodiscard]] bool IsOpen() const {
        return open_;
    }

    bool TryOpen(const std::string& key) {
        if (key == key_) {
            open_ = true;
        }
        return open_;
    }

    [[nodiscard]] const Room* GoThrough() const {
        if (!open_) {
            throw std::runtime_error{"Door is closed!"};
        }
        return to_;
    }

    explicit Door(Room* to) : open_{true}, to_{to} {
    }

    Door(Room* to, std::string key) : open_{false}, key_{std::move(key)}, to_{to} {
    }

    Door(const Door&) = delete;
    Door(Door&&) = delete;
    Door& operator=(const Door&) = delete;
    Door& operator=(Door&&) = delete;
    ~Door() = default;

   private:
    bool open_;
    const std::string key_;
    const Room* const to_;
};

class Room {
   public:
    [[nodiscard]] bool IsFinal() const {
        return is_final_;
    }

    [[nodiscard]] size_t NumKeys() const {
        return keys_.size();
    }

    [[nodiscard]] const std::string& GetKey(size_t index) const {
        return keys_[index];
    }

    [[nodiscard]] size_t NumDoors() const {
        return doors_.size();
    }

    [[nodiscard]] Door* GetDoor(size_t index) const {
        return doors_[index].get();
    }

    void AddDoor(Room* to) {
        doors_.emplace_back(std::make_unique<Door>(to));
        to->doors_.emplace_back(std::make_unique<Door>(this));
    }

    void AddDoorWithKey(Room* to, const std::string& key) {
        doors_.emplace_back(std::make_unique<Door>(to, key));
        to->doors_.emplace_back(std::make_unique<Door>(this, key));
    }

    void AddKey(const std::string& key) {
        keys_.push_back(key);
    }

    explicit Room(bool is_final) : is_final_{is_final} {
    }

    Room(const Room&) = delete;
    Room(Room&&) = delete;
    Room& operator=(const Room&) = delete;
    Room& operator=(Room&&) = delete;
    ~Room() = default;

   private:
    const bool is_final_;

    std::vector<std::unique_ptr<Door>> doors_;
    std::vector<std::string> keys_;
};
