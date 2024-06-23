#pragma once

#include "vector2.h"

#include <iostream>

// Triangle
struct Triangle
{
    Vector2 vertex[3];

    Triangle() {};
    Triangle(Vector2 (&vertices)[3])
    {
        vertex[0] = vertices[0];
        vertex[1] = vertices[1];
        vertex[2] = vertices[2];     
        if(IsClockwize())
            std::swap(vertex[1], vertex[2]);
    }

    // Check if triangle is degenerate
    inline bool IsDegenerate() const;

    // Check if triangle is clockwise
    inline bool IsClockwize() const;

    // Get the biggest edge of a triangle
    inline Segment GetBiggestEdge() const;

    // Check if point is on the inside of the edge starting from a vertex
    inline bool PointOutsideEdge(int vertexIndex, const Vector2& point) const;

    // Check if point is inside of the triangle
    inline bool PointInside(const Vector2& point) const;
    
    // Check if triangle intersects with a segment
    inline bool IntersectsWithSegment(const Segment& segment) const;
};

inline bool Triangle::IsDegenerate() const
{
    if((vertex[2] - vertex[1]) * (vertex[0] - vertex[1]))
        return false;
    return true;
}

inline bool Triangle::IsClockwize() const
{
    if((vertex[2] - vertex[1]) * (vertex[0] - vertex[1]) < .0 )
        return true;
    return false;
}

inline Segment Triangle::GetBiggestEdge() const
{
    if(vertex[0].x == vertex[1].x && vertex[0].x == vertex[2].x)
        return { vertex[0], vertex[1] };
    else
    {
        // Calculate lengths of every edge
        double maxLength{};
        int resultVertexA{0};
        int resultVertexB{0};
        for(int vertexIndex{}; vertexIndex < 3; ++vertexIndex)
        {
            int nextVertexIndex{ ( vertexIndex + 1 ) % 3};
            double edgeLength{ (vertex[nextVertexIndex] - vertex[vertexIndex]).SquaredLength() };
            if(edgeLength > maxLength)
            {
                maxLength = edgeLength;
                resultVertexA = vertexIndex;
                resultVertexB = nextVertexIndex;
            }
        };
        return { vertex[resultVertexA], vertex[resultVertexB] };
    }
}

inline bool Triangle::PointOutsideEdge(int vertexIndex, const Vector2& point) const
{
    int nextVertexIndex{ (vertexIndex + 1) % 3 };
    if((vertex[nextVertexIndex] - vertex[vertexIndex]) * (point - vertex[vertexIndex]) < .0)
        return true;
    return false;
}

inline bool Triangle::PointInside(const Vector2& point) const
{
    for(int i{}; i < 3; ++i)
        if(PointOutsideEdge(i, point))
            return false;
    return true;
}

inline bool Triangle::IntersectsWithSegment(const Segment& segment) const
{
    for(int vertexIndex{}; vertexIndex < 3; ++vertexIndex)
    {
        int nextVertexIndex{ (vertexIndex + 1) % 3 };
        if(AreIntersecting({ vertex[vertexIndex], vertex[nextVertexIndex] }, segment))
            return true;
    }
    return false;
}

// Check if triangles are intersecting
bool AreIntersecting(const Triangle& first, const Triangle& second);

std::istream& operator>>(std::istream& input, Triangle& triangle);
std::ostream& operator<<(std::ostream& output, const Triangle& triangle);
