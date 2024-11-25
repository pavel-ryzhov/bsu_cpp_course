#pragma once

#include <cstdio>

class Editor {
   public:
    class TextView {};

    void Type(char symbol) {
    }

    void ShiftLeft() {
    }

    void ShiftRight() {
    }

    void Backspace() {
    }

    void Undo() {
    }

    void Redo() {
    }

    [[nodiscard]] size_t Size() const {
        return 0;
    }

    TextView GetText(size_t pos, size_t count) const {
        return {};
    }

    size_t GetPosition() const {
        return 0;
    }
};
