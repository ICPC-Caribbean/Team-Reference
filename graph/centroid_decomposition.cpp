/*
    Algorithm:
        Centroid decomposition of a tree.

    Complexity:
        O(n log n)

    Tested:
        http://codeforces.com/problemset/problem/321/C

    Note:
        Nodes availables are those which aren't marked, i.e mk[u] is False
*/

struct tree{
    struct edge{
        int dst; // add more info if necessary
    };

    int n;
    vector<vector<edge>> adj;
    vector<int> mark, que, parent, size, max_child;

    tree(int n) : n(n){
        adj = vector<vector<edge>>(n);
        mark = vector<int>(n), que = vector<int>(n);
        parent = vector<int>(n), size = vector<int>(n);
        max_child = vector<int>(n);
    }

    void add_edge(int u, int v){
        adj[u].push_back({v});
        adj[v].push_back({u});
    }

    int centroid(int c){
        int pnt = 0, tot = 0;
        que[tot++] = c, parent[c] = -1, size[c] = 1, max_child[c] = 0;

        while (pnt < tot){
            int u = que[pnt++];
            for (auto e : adj[u]) if (e.dst != parent[u] && !mark[e.dst])
                parent[e.dst] = u, size[e.dst] = 1, max_child[e.dst] = 0, que[tot++] = e.dst;
        }

        for (int i = tot - 1; ~i; --i){
            int u = que[i];
            int bc = max(tot - size[u], max_child[u]);
            if (2 * bc <= tot) return u;
            size[parent[u]] += size[u];
            max_child[parent[u]] = max(max_child[parent[u]], size[u]);
        }

        assert(false);
        return -1;
    }

    void divide_and_conquer(int s){
        int c = centroid(s);
        mark[c] = true;

        // Do something here ...
        // Remember that nodes such that mark[u] = true where already visited

        for (auto e : adj[c])
            if (!mark[e.dst])
                divide_and_conquer(e.dst);
    }
};
