#pragma once

#include <cmath>
#include <cstdint>

struct Point {
    int x, y;
};

struct Triangle {
    Point a, b, c;
};

inline int64_t Multiply(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
    return std::abs((x1 * y2) - (y1 * x2));
}

inline bool IsPointInTriangle(const Triangle& t, const Point& pt) {
    const int64_t s1 = Multiply(pt.x - t.a.x, pt.y - t.a.y, t.b.x - t.a.x, t.b.y - t.a.y);
    const int64_t s2 = Multiply(pt.x - t.b.x, pt.y - t.b.y, t.c.x - t.b.x, t.c.y - t.b.y);
    const int64_t s3 = Multiply(pt.x - t.c.x, pt.y - t.c.y, t.a.x - t.c.x, t.a.y - t.c.y);
    if (s1 == 0 || s2 == 0 || s3 == 0) {
        return false;
    }
    const int64_t r = Multiply(t.a.x - t.b.x, t.a.y - t.b.y, t.c.x - t.b.x, t.c.y - t.b.y);
    return r == s1 + s2 + s3;
}

// inline int64_t Multiply(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
//     return (x1 * y2) - (y1 * x2);
// }
//
// inline bool IsPointInTriangle(const Triangle& t, const Point& pt) {
//     const int64_t r1 = Multiply(pt.x - t.a.x, pt.y - t.a.y, t.b.x - t.a.x, t.b.y - t.a.y);
//     const int64_t r2 = Multiply(pt.x - t.b.x, pt.y - t.b.y, t.c.x - t.b.x, t.c.y - t.b.y);
//     const int64_t r3 = Multiply(pt.x - t.c.x, pt.y - t.c.y, t.a.x - t.c.x, t.a.y - t.c.y);
//     if (r1 == 0 || r2 == 0 || r3 == 0) {
//         return false;
//     }
//     return (r1 > 0 && r2 > 0 && r3 > 0) || (r1 < 0 && r2 < 0 && r3 < 0);
// }
