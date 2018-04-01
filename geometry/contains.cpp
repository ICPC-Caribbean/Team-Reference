/*
    Algorithm:
        Determine the position of a point relative to a polygon.
        (1) General Polygon
        (2) Convex Polygon

    Complexity:
        (1) O(n)
        (2) Build O(n)
            Query O(log n)

    Tested:
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
        http://codeforces.com/contest/87/problem/E
*/

enum { OUT, ON, IN };
int contains(const polygon &P, const point &p)
{
    bool in = false;
    for (int i = 0, n = P.size(); i < n; ++i)
    {
        point a = P[i] - p, b = P[NEXT(i)] - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b))
            if (cross(a, b) < 0) in = !in;
        if (cross(a, b) == 0 && dot(a, b) <= 0)
            return ON;
    }
    return in ? IN : OUT;
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
