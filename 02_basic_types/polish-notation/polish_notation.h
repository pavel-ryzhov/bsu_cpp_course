#pragma once

#include <cctype>
#include <cstddef>
#include <stack>
#include <string>

inline std::stack<std::string> Split(const std::string& string, const std::string& delimiter) {
    if (string.empty()) {
        return {};
    }
    std::stack<std::string> result;
    size_t pos = 0;
    size_t p = 0;
    while ((p = string.find(delimiter, p)) != std::string::npos) {
        result.push(string.substr(pos, p - pos));
        p += delimiter.size();
        pos = p;
    }
    result.push(string.substr(pos));
    return result;
}

inline int EvaluateExpression(std::stack<std::string>& v) {
    if (v.size() == 1) {
        return std::stoi(v.top());
        v.pop();
    }
    const char c = v.top()[0];
    v.pop();
    int a = 0;
    int b = 0;
    if (static_cast<bool>(std::isdigit(v.top().back()))) {
        a = std::stoi(v.top());
        v.pop();
    } else {
        a = EvaluateExpression(v);
    }
    if (static_cast<bool>(std::isdigit(v.top().back()))) {
        b = std::stoi(v.top());
        v.pop();
    } else {
        b = EvaluateExpression(v);
    }
    switch (c) {
        case '-':
            return b - a;
        case '+':
            return a + b;
        default:
            return a * b;
    }
}

inline int EvaluateExpression(const std::string& expression) {
    std::stack<std::string> v = Split(expression, " ");
    return EvaluateExpression(v);
}