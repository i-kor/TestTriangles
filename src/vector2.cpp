#include "vector2.h"
#include "triangle.h"

#include <iostream>

std::istream& operator>>(std::istream& input, Vector2& vector)
{
    input >> vector.x >> vector.y;
    return input;
}

std::ostream& operator<<(std::ostream& output, const Vector2& vector)
{
    output << '(' << vector.x << ", " << vector.y << ')';
    return output;
}