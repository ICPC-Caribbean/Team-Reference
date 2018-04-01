/*
    Test:
        geometry/minkowski.cpp

    Link:
        http://codeforces.com/contest/87/problem/E
        http://codeforces.com/contest/87/submission/36864848
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

typedef complex<int64> point;
typedef vector<point> polygon;

polygon read(){
    int n; cin >> n;
    polygon p(n);
    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;
        p[i] = point(x, y);
    }
    return p;
}

void print(polygon p){
    for (auto pp : p)
        cout << pp << endl;
}

int64 cross(point a, point b){
    return imag(conj(a) * b);
}

namespace std
{
    bool operator<(point a, point b)
    {
        if (a.real() != b.real())
            return a.real() < b.real();
        return a.imag() < b.imag();
    }
}

polygon minkowski(polygon &A, polygon &B){
    int na = (int)A.size(), nb = (int)B.size();

    if (A.empty() || B.empty()) return polygon();

    rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
    rotate(B.begin(), min_element(B.begin(), B.end()), B.end());

    int pa = 0, pb = 0;

    polygon M;

    while (pa < na && pb < nb){
        M.push_back(A[pa] + B[pb]);
        double x = cross(A[(pa + 1) % na] - A[pa],
                         B[(pb + 1) % nb] - B[pb]);
        if (x <= 0) pb++;
        if (0 <= x) pa++;
    }

    while (pa < na) M.push_back(A[pa++] + B[0]);
    while (pb < nb) M.push_back(B[pb++] + A[0]);

    return M;
}

struct convex_container{
    polygon upper_envelop;
    polygon lower_envelop;

    convex_container(polygon p){
        int a = min_element(p.begin(), p.end()) - p.begin();
        int b = max_element(p.begin(), p.end()) - p.begin();

        int pnt = a;
        while (pnt != b){
            lower_envelop.push_back(p[pnt++]);
            if (pnt == p.size()) pnt = 0;
        }
        lower_envelop.push_back(p[pnt]);

        while (lower_envelop.back().real() == lower_envelop[lower_envelop.size() - 2].real())
            lower_envelop.pop_back();

        while (pnt != a){
            upper_envelop.push_back(p[pnt++]);
            if (pnt == p.size()) pnt = 0;
        }
        upper_envelop.push_back(p[pnt]);

        while (upper_envelop.back().real() == upper_envelop[upper_envelop.size() - 2].real())
            upper_envelop.pop_back();

        reverse(upper_envelop.begin(), upper_envelop.end());
    }

    bool contains(point p){
        if (p.real() < upper_envelop[0].real() || p.real() > upper_envelop.back().real())
            return false;

        int lo = 0, hi = upper_envelop.size() - 1;

        while (lo + 1 < hi){
            int m = (lo + hi) >> 1;
            if (upper_envelop[m].real() <= p.real()) lo = m;
            else hi = m;
        }

        if (cross(upper_envelop[lo + 1] - upper_envelop[lo], p - upper_envelop[lo]) > 0)
            return false;

        lo = 0, hi = lower_envelop.size() - 1;
        while (lo + 1 < hi){
            int m = (lo + hi) >> 1;
            if (lower_envelop[m].real() <= p.real()) lo = m;
            else hi = m;
        }

        if (cross(p - lower_envelop[lo], lower_envelop[lo + 1] - lower_envelop[lo]) > 0)
            return false;

        return true;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<polygon> cities(3);

    for (int i = 0; i < 3; ++i)
        cities[i] = read();

    cities[0] = minkowski(cities[0], cities[1]);
    cities[0] = minkowski(cities[0], cities[2]);

    convex_container cc(cities[0]);

    int q; cin >> q;
    while (q--){
        int64 x, y;
        cin >> x >> y;
        point p(x, y);

        if (cc.contains(p * 3LL)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }


    return 0;
}