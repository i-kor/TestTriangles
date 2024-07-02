#pragma once

#include <iostream>

struct Vector2;

struct Segment2D
{
    const Vector2& a;
    const Vector2& b;
};

struct Vector2;

// 2D Vector
struct Vector2
{
    double x;
    double y;

    Vector2(): x{ .0 }, y{ .0 } {}
    Vector2(double newX, double newY) : x{ newX }, y{ newY } {}


    inline bool IsOnSegment(const Segment2D& segment) const;

    // Squared length
    inline double SquaredLength();
};

inline bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    if(lhs.x == rhs.x && lhs.y == rhs.y)
        return true;
    return false;
}

inline bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
    return !(lhs == rhs);
}

inline bool Vector2::IsOnSegment(const Segment2D& segment) const
{
    // Check if out of rectangle
    if((x - segment.a.x) * (x - segment.b.x) > .0)
        return false;
    if((y - segment.a.y) * (y - segment.b.y) > .0)
        return false;
    // Check if not on a line
    if((segment.b.x - segment.a.x) * (y - segment.a.y) != (segment.b.y - segment.a.y) * (x - segment.a.x))
        return false;
    return true;
}

inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

// 2D Cross product (determinant of 2D matrix)
inline double operator*(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

inline double Vector2::SquaredLength()
{
    return x * x  +  y * y;
}

// Check if two segments AB and CD are intersecting
inline bool AreIntersecting(const Segment2D& first, const Segment2D& second)
{
    double denominator{ (second.b - second.a) * (first.b - first.a) };
    double alpha{ ((second.b - second.a) * (second.a - first.a)) };
    double beta{ ((first.b - first.a) * (second.a - first.a)) };
    if(!denominator)
        if(alpha == 0 && beta == 0)
        {   // Colinear
            bool vertical { first.a.x ==  first.b.x };
            double ax1 { vertical ? first.a.y : first.a.x };
            double ax2 { vertical ? first.b.y : first.b.x };
            double bx1 { vertical ? second.a.y :second.a.x };
            double bx2 { vertical ? second.b.y :second.b.x };
            if( ax2 < ax1 )
                std::swap(ax1, ax2);
            if( bx2 < bx1 )
                std::swap(bx1, bx2);
            if(std::max(ax1, bx1) <= std::min(ax2, bx2)) // Overlap
                return true;
            return false;
        }
        else
            return false; // Parallel
    alpha /= denominator;
    beta /= denominator;
    if(alpha < .0 || alpha > 1.0 || beta < .0 || beta > 1.)
        return false;
    return true;
}

std::istream& operator>>(std::istream& input, Vector2& vector);
std::ostream& operator<<(std::ostream& output, const Vector2& vector);
