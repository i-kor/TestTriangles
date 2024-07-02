#include "triangle.h"

#include <iostream>
#include <optional>
#include <limits>

#include "vector2.h"
#include "vector3.h"

bool AreIntersecting(const Triangle<Vector2, Segment2D>& first, const Triangle<Vector2, Segment2D>& second)
{
    // Check if triangle is degenerate
    bool isDegenerate[2] {first.IsDegenerate(), second.IsDegenerate()};
    if(isDegenerate[0] || isDegenerate[1])
    {
        const auto firstEdge { first.GetBiggestEdge() };
        const auto secondEdge { second.GetBiggestEdge() };
        bool isPoint[2] { firstEdge.a == firstEdge.b, secondEdge.a == secondEdge.b };
        if( isPoint[0] && isPoint[1]) // Two points
        {
            return firstEdge.a == secondEdge.a;
        }
        else if ( isPoint[0] )
        {
            if(isDegenerate[1]) // Point and segment
                return firstEdge.a.IsOnSegment(secondEdge);
            else // Point and triangle
                return second.PointInside(firstEdge.a);
        }
        else if ( isPoint[1] )
        {
            if(isDegenerate[0]) // Point and segment
                return secondEdge.a.IsOnSegment(firstEdge);
            else // Point and triangle
                return first.PointInside(secondEdge.a);
        }
        else
        {
            if(isDegenerate[0] && isDegenerate[1]) // Two segments
                return AreIntersecting(firstEdge, secondEdge);
            else if(isDegenerate[0]) // Segment and triangle
                return second.IntersectsWithSegment(firstEdge);
            else
                return first.IntersectsWithSegment(secondEdge);
        }
    }
    else
    {
        // For each edge of a first triangle check if all vertices of the second triangle is outside
        for(int edge{}; edge < 3; ++edge)
            if(first.PointOutsideEdge(edge, second.vertex[0]) &&
            first.PointOutsideEdge(edge, second.vertex[1]) &&
            first.PointOutsideEdge(edge, second.vertex[2]))
                return false;
        // For each edge of a second triangle check if all vertices of the first triangle is outside
        for(int edge{}; edge < 3; ++edge)
            if(second.PointOutsideEdge(edge, first.vertex[0]) &&
            second.PointOutsideEdge(edge, first.vertex[1]) &&
            second.PointOutsideEdge(edge, first.vertex[2]))
                return false;
    }
    return true;
}


// Möller–Trumbore intersection algorithm
// Code used from https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
std::optional<float> RayIntersectsTriangle(const Vector3 &ray_origin,
    const Vector3& ray_vector,
    const Triangle<Vector3, Segment3D>& triangle)
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    Vector3 edge1 = triangle.vertex[1] - triangle.vertex[0];
    Vector3 edge2 = triangle.vertex[2] - triangle.vertex[0];
    Vector3 ray_cross_e2 = ray_vector * edge2;
    float det = Dot(edge1, ray_cross_e2);

    if (det > -epsilon && det < epsilon)
    // This ray is parallel to this triangle.
    // Here we should also check if a ray is in a plane of a triangle and then if it's projection to a plane intersects with a triangle projection
    // We should use 2D version of algorithm for this task
        return {};

    float inv_det = 1.0 / det;
    Vector3 s = ray_origin - triangle.vertex[0];
    float u = inv_det * Dot(s, ray_cross_e2);

    if (u < 0 || u > 1)
        return {};

    Vector3 s_cross_e1 = s * edge1;
    float v = inv_det * Dot(ray_vector, s_cross_e1);

    if (v < 0 || u + v > 1)
        return {};

    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = inv_det * Dot(edge2, s_cross_e1);

    if (t > epsilon) // ray intersection
    {
        return  t;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return {};
}

// This implementation is only for demonstrating an approach
// It doesn't yet properly process borderline cases such as overlapping triangles, edges in a plane of a triangle
// It isn't properly tested and debugged
bool AreIntersecting(const Triangle<Vector3, Segment3D>& first, const Triangle<Vector3, Segment3D>& second)
{
    // Check if any of the edges intersects with a triangle
    for(int vertexIndex{}; vertexIndex < 3; ++vertexIndex)
    {
        auto nextVertexIndex{ (vertexIndex + 1) % 3 };
        // First triangle edges
        auto check { RayIntersectsTriangle(first.vertex[vertexIndex], first.vertex[nextVertexIndex], second) };
        // Intersection point is on a segment
        if(check && *check >= .0 && *check <= 1.0) 
            return true;
        // Second triangle edges
        check = RayIntersectsTriangle(second.vertex[vertexIndex], second.vertex[nextVertexIndex], first);
        // Intersection point is on a segment
        if(check && *check >= .0 && *check <= 1.0)
            return true;
    }
    return false;
}
