#pragma once

#include <cstdint>
#include <memory>
#include <sstream>

class Tokenizer {
   public:
    explicit Tokenizer(std::istream* in) : in_{in} {
        Consume();
    }

    enum TokenType : uint8_t { kNumber, kSymbol, kEnd };

    void Consume() {
    }

    TokenType GetType() const {
    }

    int64_t GetNumber() const {
    }

    char GetSymbol() const {
    }

   private:
    std::istream* in_;

    TokenType type_;
    int64_t number_;
    char symbol_;
};

class Expression {
   public:
    virtual ~Expression() = default;
    virtual int64_t Evaluate() const = 0;
};

std::unique_ptr<Expression> ParseExpression(Tokenizer* tokenizer) {
    return nullptr;
}
