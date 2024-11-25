// NOLINTBEGIN
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

std::string LimitedGetline(std::ifstream& in) {
    constexpr auto kMaxSize = 80;
    std::string line;
    while (line.size() <= kMaxSize) {
        if (auto c = in.get(); in && (c != '\n')) {
            line.push_back(static_cast<char>(c));
        } else {
            return line;
        }
    }
    std::cout << "Line is too long\n";
    std::exit(0);  // NOLINT(concurrency-mt-unsafe)
}

// This class is following rule of 5.
// https://en.cppreference.com/w/cpp/language/rule_of_three#Rule_of_five
class SlowNumber {
   public:
    explicit SlowNumber(int value) : value_{new int{value}} {
    }

    SlowNumber(SlowNumber&& other) noexcept : value_{other.value_} {
        other.value_ = nullptr;
    }

    SlowNumber(const SlowNumber& other) : value_{new int{*other.value_}} {
    }

    SlowNumber& operator=(SlowNumber&& other) noexcept {
        delete value_;

        value_ = other.value_;
        other.value_ = nullptr;
        return *this;
    }

    SlowNumber& operator=(const SlowNumber& other) {
        if (value_ != nullptr) {
            delete value_;
            value_ = nullptr;
        }

        if (other.value_ != nullptr) {
            value_ = new int{*other.value_};  // NOLINT(cppcoreguidelines-owning-memory)
        }
        return *this;
    }

    ~SlowNumber() {
        delete value_;
    }

    [[nodiscard]] int Value() const {
        return *value_;
    }

   private:
    int* value_ = nullptr;
};

bool InRange(const std::vector<std::shared_ptr<SlowNumber>>& stack, int index) {
    return (index >= 0) && (index < std::ssize(stack));
}

int main() {  // NOLINT(readability-function-cognitive-complexity,bugprone-exception-escape)
    std::ifstream in("13_crashme_warmup/rule-of-5/input.txt");
    if (!in) {
        std::cout << "Bad file path\n";
        std::exit(0);  // NOLINT(concurrency-mt-unsafe)
    }
    std::vector<std::shared_ptr<SlowNumber>> stack;

    for (auto i = 0; i < 1000; ++i) {
        if (auto cmd = LimitedGetline(in); cmd == "push") {
            auto value = 0;
            in >> value;
            in.get();  // eat up newline
            stack.push_back(std::make_shared<SlowNumber>(value));
        } else if (cmd == "pop") {
            if (!stack.empty()) {
                stack.pop_back();
            } else {
                std::cout << "error: stack is empty\n";
            }
        } else if (cmd == "print") {
            for (const auto& v : stack) {
                std::cout << v->Value() << '\n';
            }
        } else if (cmd == "swap") {
            auto i = 0;
            auto j = 0;
            in >> i >> j;
            in.get();  // eat up newline

            if (!InRange(stack, i) || !InRange(stack, j)) {
                std::cout << "error: invalid index\n";
                continue;
            }

            std::swap(*(stack[i]), *(stack[j]));
        } else if (cmd == "dup") {
            if (stack.empty()) {
                std::cout << "error: stack is empty\n";
                continue;
            }

            stack.push_back(stack.back());
        } else if (cmd == "pop_carry") {
            if (stack.size() < 2) {
                std::cout << "error: stack size must be greater than 2\n";
                continue;
            }

            *(stack[stack.size() - 2]) = std::move(*stack.back());
            stack.pop_back();
        } else if (cmd.empty()) {
            break;
        } else {
            std::cout << "unknown cmd\n";
        }
    }
}

// NOLINTEND
