#include "vector3.h"
#include "triangle.h"

#include <iostream>

std::istream& operator>>(std::istream& input, Vector3& vector)
{
    input >> vector.x >> vector.y >> vector.z;
    return input;
}

std::ostream& operator<<(std::ostream& output, const Vector3& vector)
{
    output << '(' << vector.x << ", " << vector.y << ", " << vector.z << ')';
    return output;
}