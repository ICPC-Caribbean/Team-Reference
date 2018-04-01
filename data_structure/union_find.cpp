/*
    Algorithm:
        Union find (Disjoint set)
        https://en.wikipedia.org/wiki/Disjoint-set_data_structure

    Tested:
        http://matcomgrader.com/problem/9464/construyendo-la-red-de-carreteras/
*/

struct union_find
{
    vector<int> p;

    union_find(int n) : p(n, -1) {}

    bool join(int u, int v)
    {
        if ((u = root(u)) == (v = root(v)))
            return false;
        if (p[u] > p[v])
            swap(u, v);
        p[u] += p[v];
        p[v] = u;
        return true;
    }

    int root(int u)
    {
        return p[u] < 0 ? u : p[u] = root(p[u]);
    }
};
