#pragma once

#include <iostream>

struct Vector3;

struct Segment3D
{
    const Vector3& a;
    const Vector3& b;
};

// 3D Vector
struct Vector3
{
    double x;
    double y;
    double z;

    Vector3(): x{ .0 }, y{ .0 }, z{ .0 } {}
    Vector3(double newX, double newY, double newZ) : x{ newX }, y{ newY }, z{ newZ } {}

    inline double SquaredLength();
};

inline bool operator==(const Vector3& lhs, const Vector3& rhs)
{
    if(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
        return true;
    return false;
}

inline bool operator!=(const Vector3& lhs, const Vector3& rhs)
{
    return !(lhs == rhs);
}

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

// Scale vector
inline Vector3 operator*(const Vector3& vector, double scale)
{
    return Vector3(vector.x * scale, vector.y * scale, vector.z * scale);
}

// Cross product
inline Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
{
    double x = lhs.x * rhs.z - lhs.z * rhs.y;
    double y = lhs.z * rhs.x - lhs.x * rhs.z;
    double z = lhs.x * rhs.y - lhs.y * rhs.x;
    return Vector3(x, y, z);
}

// Dot product
inline double Dot(Vector3 lhs, Vector3 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline double Vector3::SquaredLength()
{
    return x * x  +  y * y + z * z;
}

std::istream& operator>>(std::istream& input, Vector3& vector);
std::ostream& operator<<(std::ostream& output, const Vector3& vector);
