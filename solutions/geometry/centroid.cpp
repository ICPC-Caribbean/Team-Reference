/*
    Test:
        geometry/centroid.cpp

    Link:
        http://www.spoj.com/problems/STONE/
*/

#include <bits/stdc++.h>

using namespace std;

typedef complex<double> point;
typedef vector<point> polygon;

#define NEXT(i) (((i) + 1) % n)

double cross(point a, point b) { return imag(conj(a) * b); }

double area2(const polygon &P)
{
    double A = 0;
    for (int i = 0, n = P.size(); i < n; ++i)
        A += cross(P[i], P[NEXT(i)]);
    return A;
}

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

int main(){
    int t; cin >> t;

    while (t-->0){
        int n; cin >> n;

        polygon P(n);

        for (int i = 0; i < n; ++i){
            double x, y; cin >> x >> y;
            P[i] = point(x, y);
        }

        point c = centroid(P);

        cout.precision(2);
        cout << fixed << c.real() << " " << c.imag() << endl;
    }
}