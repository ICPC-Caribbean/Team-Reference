/*
    Algorithm:
        Pick's theorem
        A = I + B/2 - 1:
        A = Area of the polygon
        I = Number of integer coordinates points inside
        B = Number of integer coordinates points on the boundary

    Complexity:
        O(n)

    Tested:
        http://lightoj.com/volume_showproblem.php?problem=1418

    Note:
        Polygon's vertex MUST have integer coordinates (consider using long long)
*/

long long points_on_segment(const segment &s)
{
    point p = s.p - s.q;
    return __gcd(abs(p.real()), abs(p.imag()));
}

// <Lattice points (not in boundary), Lattice points on boundary>
pair<long long, long long> pick(polygon &P)
{
    long long A = area2(P), B = 0, I = 0;
    for (int i = 0, n = P.size(); i < n; ++i)
        B += points_on_segment({P[i], P[NEXT(i)]});
    A = abs(A);
    I = (A - B) / 2 + 1;
    return {I, B};
}
