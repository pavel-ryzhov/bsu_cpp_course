#pragma once

#include <cctype>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_set>
#include <utility>

inline bool IsSymbol(char c) {
    return std::unordered_set{'+', '-', '*', '/', '(', ')'}.contains(c);
}

class Tokenizer {
   public:
    explicit Tokenizer(std::istream* in) : in_{in} {
        Consume();
    }

    enum TokenType : uint8_t { kNumber, kSymbol, kEnd };

    void Consume() {
        if (!in_->good()) {
            type_ = kEnd;
            return;
        }
        const auto c = static_cast<char>(in_->peek());
        if (static_cast<bool>(std::isdigit(c))) {
            type_ = kNumber;
            *in_ >> number_;
            return;
        }
        in_->get();
        if (IsSymbol(c)) {
            type_ = kSymbol;
            symbol_ = c;
        } else {
            Consume();
        }
    }

    [[nodiscard]] TokenType GetType() const {
        return type_;
    }

    [[nodiscard]] int64_t GetNumber() const {
        return number_;
    }

    [[nodiscard]] char GetSymbol() const {
        return symbol_;
    }

   private:
    std::istream* in_;

    TokenType type_ = kEnd;
    int64_t number_ = 0;
    char symbol_ = 0;
};

class Expression {
   public:
    Expression() = default;
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
    Expression(Expression&&) = delete;
    Expression& operator=(Expression&&) = delete;
    virtual ~Expression() = default;

    [[nodiscard]] virtual int64_t Evaluate() const = 0;
};

class ConstantExpression : public Expression {
   public:
    explicit ConstantExpression(int64_t value) : value_(value) {
    }

    [[nodiscard]] int64_t Evaluate() const override {
        return value_;
    }

   private:
    int64_t value_;
};

class PlusExpression : public Expression {
   public:
    enum Action : uint8_t { kAdd, kSubstract };

    explicit PlusExpression(Tokenizer* tokenizer)
        : PlusExpression(std::make_unique<ConstantExpression>(0), tokenizer) {
    }

    PlusExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {
    }

    PlusExpression(
        std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, Action action)
        : left_(std::move(left)), right_(std::move(right)), action_(action) {
    }

    PlusExpression(std::unique_ptr<Expression> left, Tokenizer* tokenizer, Action action);

    PlusExpression(std::unique_ptr<Expression> left, Tokenizer* tokenizer)
        : PlusExpression(std::move(left), tokenizer, kAdd) {
    }

    [[nodiscard]] int64_t Evaluate() const override {
        return action_ == kAdd ? left_->Evaluate() + right_->Evaluate()
                               : left_->Evaluate() - right_->Evaluate();
    }

   private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
    Action action_ = kAdd;
};

class UnaryMinusExpression : public Expression {
   public:
    explicit UnaryMinusExpression(std::unique_ptr<Expression> expression)
        : expression_(std::move(expression)) {
    }

    [[nodiscard]] int64_t Evaluate() const override {
        return -expression_->Evaluate();
    }

   private:
    std::unique_ptr<Expression> expression_;
};

class BracketExpression : public Expression {
   public:
    explicit BracketExpression(Tokenizer* tokenizer) {
        switch (tokenizer->GetType()) {
            case Tokenizer::kNumber: {
                expression_ = std::make_unique<ConstantExpression>(tokenizer->GetNumber());
                tokenizer->Consume();
                break;
            }
            case Tokenizer::kSymbol: {
                const char symbol = tokenizer->GetSymbol();
                tokenizer->Consume();
                if (symbol == '(') {
                    expression_ = std::make_unique<PlusExpression>(tokenizer);
                    if (tokenizer->GetSymbol() == ')') {
                        tokenizer->Consume();
                    }
                } else {
                    expression_ = std::make_unique<UnaryMinusExpression>(
                        std::make_unique<BracketExpression>(tokenizer));
                }
                break;
            }
            default:
                throw std::invalid_argument("Invalid expression!");
        }
    }

    [[nodiscard]] int64_t Evaluate() const override {
        return expression_->Evaluate();
    }

   private:
    std::unique_ptr<Expression> expression_;
};

class MultiplyExpression : public Expression {
   public:
    enum Action : uint8_t { kMultiply, kDivide };

    explicit MultiplyExpression(Tokenizer* tokenizer)
        : MultiplyExpression(std::make_unique<ConstantExpression>(1), tokenizer) {
    }

    MultiplyExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {
    }

    MultiplyExpression(
        std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, Action action)
        : left_(std::move(left)), right_(std::move(right)), action_(action) {
    }

    MultiplyExpression(std::unique_ptr<Expression> left, Tokenizer* tokenizer, Action action);

    MultiplyExpression(std::unique_ptr<Expression> left, Tokenizer* tokenizer)
        : MultiplyExpression(std::move(left), tokenizer, kMultiply) {
    }

    [[nodiscard]] int64_t Evaluate() const override {
        return action_ == kMultiply ? left_->Evaluate() * right_->Evaluate()
                                    : left_->Evaluate() / right_->Evaluate();
    }

   private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
    Action action_ = kMultiply;
};

inline PlusExpression::PlusExpression(
    std::unique_ptr<Expression> left, Tokenizer* tokenizer, Action action)
    : action_(action) {
    left_ = std::make_unique<PlusExpression>(
        std::move(left), std::make_unique<MultiplyExpression>(tokenizer), action_);
    switch (tokenizer->GetType()) {
        case Tokenizer::kSymbol: {
            const char symbol = tokenizer->GetSymbol();
            if (symbol == '+' || symbol == '-') {
                tokenizer->Consume();
                action_ = kAdd;
                right_ = std::make_unique<PlusExpression>(
                    std::move(left_), tokenizer, symbol == '+' ? kAdd : kSubstract);
                left_ = std::make_unique<ConstantExpression>(0);
            } else {
                right_ = std::make_unique<ConstantExpression>(0);
            }
            break;
        }
        case Tokenizer::kEnd: {
            right_ = std::make_unique<ConstantExpression>(0);
            break;
        }
        default:
            throw std::invalid_argument("Invalid expression!");
    }
}

inline MultiplyExpression::MultiplyExpression(
    std::unique_ptr<Expression> left, Tokenizer* tokenizer, Action action)
    : action_(action) {
    left_ = std::make_unique<MultiplyExpression>(
        std::move(left), std::make_unique<BracketExpression>(tokenizer), action_);
    switch (tokenizer->GetType()) {
        case Tokenizer::kSymbol: {
            const char symbol = tokenizer->GetSymbol();
            if (symbol == '*' || symbol == '/') {
                tokenizer->Consume();
                action_ = kMultiply;
                right_ = std::make_unique<MultiplyExpression>(
                    std::move(left_), tokenizer, symbol == '*' ? kMultiply : kDivide);
                left_ = std::make_unique<ConstantExpression>(1);
            } else {
                right_ = std::make_unique<ConstantExpression>(1);
            }
            break;
        }
        case Tokenizer::kEnd: {
            right_ = std::make_unique<ConstantExpression>(1);
            break;
        }
        default:
            throw std::invalid_argument("Invalid expression!");
    }
}

inline std::unique_ptr<Expression> ParseExpression(Tokenizer* tokenizer) {
    return std::make_unique<PlusExpression>(tokenizer);
}