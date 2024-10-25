#pragma once

#include <cstdint>

struct Point {
    int x, y;
};

struct Triangle {
    Point a, b, c;
};

inline int64_t Multiply(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
    return (x1 * y2) - (y1 * x2);
}

inline bool IsPointInTriangle(const Triangle& t, const Point& pt) {
    const int64_t r1 = Multiply(
        static_cast<int64_t>(pt.x) - t.a.x, static_cast<int64_t>(pt.y) - t.a.y,
        static_cast<int64_t>(t.b.x) - t.a.x, static_cast<int64_t>(t.b.y) - t.a.y);
    const int64_t r2 = Multiply(
        static_cast<int64_t>(pt.x) - t.b.x, static_cast<int64_t>(pt.y) - t.b.y,
        static_cast<int64_t>(t.c.x) - t.b.x, static_cast<int64_t>(t.c.y) - t.b.y);
    const int64_t r3 = Multiply(
        static_cast<int64_t>(pt.x) - t.c.x, static_cast<int64_t>(pt.y) - t.c.y,
        static_cast<int64_t>(t.a.x) - t.c.x, static_cast<int64_t>(t.a.y) - t.c.y);
    if (r1 == 0 || r2 == 0 || r3 == 0) {
        return false;
    }
    return (r1 > 0 && r2 > 0 && r3 > 0) || (r1 < 0 && r2 < 0 && r3 < 0);
}
