/*
    Algorithm:
        Centroid of a (possibly nonconvex) polygon

    Complexity:
        O(n)

    Tested:
        http://www.spoj.com/problems/STONE/

    Note:
        Coordinates must be listed in a cw or ccw.
*/

#include <geometry/basics.cpp>

point centroid(const polygon &P)
{
    point c(0, 0);
    double scale = 3.0 * area2(P); // area2 = 2 * polygon_area
    for (int i = 0, n = P.size(); i < n; ++i)
    {
        int j = NEXT(i);
        c = c + (P[i] + P[j]) * (cross(P[i], P[j]));
    }
    return c / scale;
}
