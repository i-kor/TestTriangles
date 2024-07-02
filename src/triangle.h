#pragma once

#include <iostream>
#include "vector2.h"
#include "vector3.h"

// Triangle
template<typename Vector, typename Segment>
struct Triangle
{
    Vector vertex[3];

    Triangle() {};
    Triangle(Vector (&vertices)[3])
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
    inline bool PointOutsideEdge(int vertexIndex, const Vector& point) const;

    // Check if point is inside of the triangle
    inline bool PointInside(const Vector& point) const;
    
    // Check if triangle intersects with a segment
    inline bool IntersectsWithSegment(const Segment& segment) const;
};

template<typename Vector, typename Segment>
inline bool Triangle<Vector, Segment>::IsDegenerate() const
{
    if((vertex[2] - vertex[1]) * (vertex[0] - vertex[1]))
        return false;
    return true;
}

template<typename Vector, typename Segment>
inline bool Triangle<Vector, Segment>::IsClockwize() const
{
    if((vertex[2] - vertex[1]) * (vertex[0] - vertex[1]) < .0 )
        return true;
    return false;
}

template<typename Vector, typename Segment>
inline Segment Triangle<Vector, Segment>::GetBiggestEdge() const
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

template<typename Vector, typename Segment>
inline bool Triangle<Vector, Segment>::PointOutsideEdge(int vertexIndex, const Vector& point) const
{
    int nextVertexIndex{ (vertexIndex + 1) % 3 };
    if((vertex[nextVertexIndex] - vertex[vertexIndex]) * (point - vertex[vertexIndex]) < .0)
        return true;
    return false;
}

template<typename Vector, typename Segment>
inline bool Triangle<Vector, Segment>::PointInside(const Vector& point) const
{
    for(int i{}; i < 3; ++i)
        if(PointOutsideEdge(i, point))
            return false;
    return true;
}

template<typename Vector, typename Segment>
inline bool Triangle<Vector, Segment>::IntersectsWithSegment(const Segment& segment) const
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
bool AreIntersecting(const Triangle<Vector2, Segment2D>& first, const Triangle<Vector2, Segment2D>& second);
bool AreIntersecting(const Triangle<Vector3, Segment3D>& first, const Triangle<Vector3, Segment3D>& second);

template<typename Vector, typename Segment>
std::istream& operator>>(std::istream& input, Triangle<Vector, Segment>& triangle)
{
    input >> triangle.vertex[0] >> triangle.vertex[1] >> triangle.vertex[2];
    return input;
}

template<typename Vector, typename Segment>
std::ostream& operator<<(std::ostream& output, const Triangle<Vector, Segment>& triangle)
{
    output << '{' << triangle.vertex[0] << "; " << triangle.vertex[1] << "; " << triangle.vertex[2]  << '}';
    return output;
}
