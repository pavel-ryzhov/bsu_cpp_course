#pragma once

#include <cstddef>
#include <memory>
#include <stack>
#include <string>
#include <utility>

class Editor;

class Command {
   public:
    explicit Command(Editor* editor) : editor_(editor) {
    }

    virtual bool Execute() = 0;
    virtual void Undo() = 0;
    virtual ~Command() = default;

    [[nodiscard]] Editor* GetEditor() const {
        return editor_;
    }

    Command(const Command&) = delete;
    Command(Command&&) = delete;
    Command& operator=(const Command&) = delete;
    Command& operator=(Command&&) = delete;

   private:
    Editor* editor_;
};

class Editor {
   public:
    class TextView {
       public:
        class Iterator {
           public:
            Iterator(
                const std::string::const_iterator& begin1, const std::string::const_iterator& end1,
                const std::string::const_reverse_iterator& begin2,
                const std::string::const_reverse_iterator& end2)
                : begin1_(begin1), end1_(end1), begin2_(begin2), end2_(end2) {
            }

            Iterator(
                const std::string& before, const std::string& after, size_t pos, size_t count) {
                if (pos < before.size()) {
                    begin1_ = before.cbegin() +
                              static_cast<std::string::const_iterator::difference_type>(pos);
                    begin2_ = after.crbegin();
                } else {
                    begin1_ = before.cend();
                    begin2_ = after.crbegin() +
                              static_cast<std::string::const_reverse_iterator::difference_type>(
                                  pos - before.size());
                }
                if (pos + count < before.size()) {
                    end1_ = before.cbegin() +
                            static_cast<std::string::const_iterator::difference_type>(pos + count);
                    end2_ = after.crbegin();
                } else {
                    end1_ = before.cend();
                    end2_ = after.crbegin() +
                            static_cast<std::string::const_reverse_iterator::difference_type>(
                                pos + count - before.size());
                }
            }

            Iterator() = default;

            Iterator& operator++() {
                if (begin1_ != end1_) {
                    ++begin1_;
                } else {
                    ++begin2_;
                }
                return *this;
            }

            Iterator operator++(int) {
                Iterator tmp = *this;
                if (begin1_ != end1_) {
                    ++begin1_;
                } else {
                    ++begin2_;
                }
                return tmp;
            }

            const char& operator*() const {
                return begin1_ == end1_ ? *begin2_ : *begin1_;
            }

            bool operator!=(const Iterator& other) const {
                return begin1_ != other.begin1_ || begin2_ != other.begin2_;
            }

            [[nodiscard]] Iterator End() const {
                return {end1_, end1_, end2_, end2_};
            }

           private:
            std::string::const_iterator begin1_;
            std::string::const_iterator end1_;
            std::string::const_reverse_iterator begin2_;
            std::string::const_reverse_iterator end2_;
        };

        [[nodiscard]] Iterator begin() const {
            return begin_;
        }

        [[nodiscard]] Iterator end() const {
            return end_;
        }

        TextView(const std::string& before, const std::string& after, size_t pos, size_t count) {
            const auto it = Iterator(before, after, pos, count);
            begin_ = it;
            end_ = it.End();
        }

       private:
        Iterator begin_;
        Iterator end_;
    };

    void Type(char symbol);

    void ShiftLeft();

    void ShiftRight();

    void Backspace();

    void Undo() {
        if (!executed_commands_.empty()) {
            undone_commands_.emplace(std::move(executed_commands_.top()));
            undone_commands_.top()->Undo();
            executed_commands_.pop();
        }
    }

    void Redo() {
        if (!undone_commands_.empty()) {
            executed_commands_.emplace(std::move(undone_commands_.top()));
            executed_commands_.top()->Execute();
            undone_commands_.pop();
        }
    }

    [[nodiscard]] size_t Size() const {
        return before_.size() + after_.size();
    }

    [[nodiscard]] TextView GetText(size_t pos, size_t count) const {
        return {before_, after_, pos, count};
    }

    [[nodiscard]] size_t GetPosition() const {
        return before_.size();
    }

   private:
    friend class TypeCommand;
    friend class ShiftLeftCommand;
    friend class ShiftRightCommand;
    friend class BackspaceCommand;
    std::string before_;
    std::string after_;
    std::stack<std::unique_ptr<Command>> executed_commands_;
    std::stack<std::unique_ptr<Command>> undone_commands_;

    void MoveCharLeft() {
        before_.push_back(after_.back());
        after_.pop_back();
    }

    void MoveCharRight() {
        after_.push_back(before_.back());
        before_.pop_back();
    }

    void ExecuteCommand(std::unique_ptr<Command> command) {
        if (command->Execute()) {
            executed_commands_.emplace(std::move(command));
            undone_commands_ = std::stack<std::unique_ptr<Command>>();
        }
    }
};

class TypeCommand : public Command {
   public:
    TypeCommand(Editor* editor, char c) : Command{editor}, c_{c} {
    }

    bool Execute() override {
        GetEditor()->before_.push_back(c_);
        return true;
    }

    void Undo() override {
        GetEditor()->before_.pop_back();
    }

   private:
    char c_;
};

class ShiftLeftCommand : public Command {
   public:
    explicit ShiftLeftCommand(Editor* editor) : Command{editor} {
    }

    bool Execute() override {
        if (!GetEditor()->before_.empty()) {
            GetEditor()->MoveCharRight();
            return true;
        }
        return false;
    }

    void Undo() override {
        GetEditor()->MoveCharLeft();
    }
};

class ShiftRightCommand : public Command {
   public:
    explicit ShiftRightCommand(Editor* editor) : Command{editor} {
    }

    bool Execute() override {
        if (!GetEditor()->after_.empty()) {
            GetEditor()->MoveCharLeft();
            return true;
        }
        return false;
    }

    void Undo() override {
        GetEditor()->MoveCharRight();
    }
};

class BackspaceCommand : public Command {
   public:
    explicit BackspaceCommand(Editor* editor) : Command{editor} {
    }

    bool Execute() override {
        if (!GetEditor()->before_.empty()) {
            c_ = GetEditor()->before_.back();
            GetEditor()->before_.pop_back();
            return true;
        }
        return false;
    }

    void Undo() override {
        GetEditor()->before_.push_back(c_);
    }

   private:
    char c_ = '\0';
};

inline void Editor::Type(char symbol) {
    ExecuteCommand(std::make_unique<TypeCommand>(this, symbol));
}

inline void Editor::ShiftLeft() {
    ExecuteCommand(std::make_unique<ShiftLeftCommand>(this));
}

inline void Editor::ShiftRight() {
    ExecuteCommand(std::make_unique<ShiftRightCommand>(this));
}

inline void Editor::Backspace() {
    ExecuteCommand(std::make_unique<BackspaceCommand>(this));
}
