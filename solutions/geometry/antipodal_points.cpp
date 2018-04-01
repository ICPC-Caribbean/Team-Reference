/*
    Test:
        geometry/antipodal_points.cpp

    Link:
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B

    Note:
        Find the diameter of a convex polygon
*/

#include <bits/stdc++.h>

using namespace std;

typedef complex<double> point;
typedef vector<point> polygon;

#define NEXT(i) (((i) + 1) % n)

double cross(point a, point b) { return imag(conj(a) * b); }
double area2(point a, point b, point c) { return cross(b - a, c - a); }

vector<pair<int, int>> antipodal(const polygon &P)
{
    vector<pair<int, int>> ans;
    int n = P.size();

    if (P.size() == 2)
        ans.push_back({ 0, 1 });

    if (P.size() < 3)
        return ans;

    int q0 = 0;

    while (abs(area2(P[n - 1], P[0], P[NEXT(q0)]))
            > abs(area2(P[n - 1], P[0], P[q0])))
        ++q0;

    for (int q = q0, p = 0; q != 0 && p <= q0; ++p)
    {
        ans.push_back({ p, q });

        while (abs(area2(P[p], P[NEXT(p)], P[NEXT(q)]))
                > abs(area2(P[p], P[NEXT(p)], P[q])))
        {
            q = NEXT(q);
            if (p != q0 || q != 0)
                ans.push_back({ p, q });
            else
                return ans;
        }

        if (abs(area2(P[p], P[NEXT(p)], P[NEXT(q)]))
                == abs(area2(P[p], P[NEXT(p)], P[q])))
        {
            if (p != q0 || q != n - 1)
                ans.push_back({ p, NEXT(q) });
            else
                ans.push_back({ NEXT(p), q });
        }
    }

    return ans;
}

int main(){
    int n; cin >> n;

    polygon P(n);

    for (int i = 0; i < n; ++i){
        double x, y;
        cin >> x >> y;
        P[i] = point(x, y);
    }

    auto apod = antipodal(P);

    double diameter = 0.;

    for (auto a : apod)
        diameter = max(diameter, abs(P[a.first] - P[a.second]));

    cout.precision(17);

    cout << fixed << diameter << endl;
}