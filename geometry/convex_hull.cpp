/*
    Algorithm:
        Find convex hull of a set of 2d points

    Complexity:
        O(n log n)

    Tested:
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A

    Note:
        Convex hull don't contain points on the sides.
        (Replace less equal condition for strictly less to keep points in the sides)
*/

#include <geometry/basics.cpp>

polygon convex_hull(vector<point> &P)
{
    int n = P.size(), k = 0;
    vector<point> h(2 * n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; h[k++] = P[i++])
        while (k >= 2 && area2(h[k - 2], h[k - 1], P[i]) <= 0) --k;
    for (int i = n - 2, t = k + 1; i >= 0; h[k++] = P[i--])
        while (k >= t && area2(h[k - 2], h[k - 1], P[i]) <= 0) --k;
    return polygon(h.begin(), h.begin() + k - (k > 1));
}
