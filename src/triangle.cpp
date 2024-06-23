#include "triangle.h"

#include <iostream>

bool AreIntersecting(const Triangle& first, const Triangle& second)
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


std::istream& operator>>(std::istream& input, Triangle& triangle)
{
    input >> triangle.vertex[0] >> triangle.vertex[1] >> triangle.vertex[2];
    return input;
}

std::ostream& operator<<(std::ostream& output, const Triangle& triangle)
{
    output << '{' << triangle.vertex[0] << "; " << triangle.vertex[1] << "; " << triangle.vertex[2]  << '}';
    return output;
}
