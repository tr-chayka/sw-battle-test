#pragma once 
#include <cstdint>

namespace sw::sim
{
    struct Point
    {
        int32_t x;
        int32_t y;

        Point operator + (const Point& p) const { return {x + p.x, y + p.y}; }
        Point operator - (const Point& p) const { return {x - p.x, y - p.y}; }
        
        int32_t length2() const { return x * x + y * y; } 
        int32_t distance2(const Point& p) const { return (p - *this).length2(); }

        bool operator == (const Point& p) const { return x == p.x && y == p.y; }
        bool operator != (const Point& p) const { return !(*this == p); }

        Point norm() const
        {
            int32_t nx = x ? x / abs(x) : 0;
            int32_t ny = y ? y / abs(y) : 0;

            return {nx, ny};
        }
    };
}