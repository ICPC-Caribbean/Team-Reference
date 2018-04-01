/*
    Name:
        A Graph Problem

    Test:
        graph/dinic.cpp

    Link:
        https://www.hackerrank.com/contests/w30/challenges/a-graph-problem/problem
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

template<typename F, typename R = F>
struct dinic
{
    typedef F flow_type;
    typedef R result_type;

    struct edge
    {
        int src, dst, rev;
        flow_type flow, cap;
    };

    dinic(int n) : adj(n), que(n), level(n), iter(n) {}

    bool side_of_S(int u) { return level[u] == -1; }

    const vector<edge>& operator[](int u) const { return adj[u]; }
    vector<edge>& operator[](int u) { return adj[u]; }

    int add_edge(int src, int dst, flow_type cap, flow_type rcap = 0)
    {
        adj[src].push_back({src, dst, (int) adj[dst].size(), 0, cap});
        if (src == dst) adj[src].back().rev++;
        adj[dst].push_back({dst, src, (int) adj[src].size() - 1, 0, rcap});
        return adj[src].size() - 1 - (src == dst);
    }

    static constexpr flow_type oo = numeric_limits<flow_type>::max();

    result_type max_flow(int source, int sink)
    {
        for (int u = 0; u < adj.size(); ++u)
            for (edge &e : adj[u]) e.flow = 0;
        result_type flow = 0;
        while (bfs(source, sink))
        {
            std:fill(iter.begin(), iter.end(), 0);
            for (flow_type f; (f = dfs(source, sink, oo)) > 0;)
                flow += f;
        }
        return flow;
    }

    void reset(double cap){
        for (int u = 0; u < adj.size(); ++u)
            for (auto &e : adj[u]){
                e.flow = 0.;
                if (e.dst == 1)
                    e.cap = cap;
            }
    }

private:
    vector<vector<edge>> adj;
    vector<int> que;
    vector<int> level;
    vector<int> iter;

    inline edge& rev(const edge &e) { return adj[e.dst][e.rev]; }

    bool bfs(int source, int sink)
    {
        int front = 0, back = 0;
        fill(level.begin(), level.end(), -1);
        level[sink] = 0;
        for (que[back++] = sink; front < back && level[source] == -1; ++front)
        {
            int u = que[front];
            for (const edge &e : adj[u])
                if (level[e.dst] == -1 && rev(e).flow < rev(e).cap)
                {
                    level[e.dst] = 1 + level[u];
                    que[back++] = e.dst;
                }
        }
        return level[source] != -1;
    }

    flow_type dfs(int source, int sink, flow_type flow)
    {
        if (source == sink) return flow;
        for (int &index = iter[source]; index != adj[source].size(); ++index)
        {
            edge &e = adj[source][index];
            if (e.flow < e.cap && level[source] == 1 + level[e.dst])
            {
                flow_type delta = dfs(e.dst, sink, min(flow, e.cap - e.flow));
                if (delta > 0)
                {
                    e.flow += delta;
                    rev(e).flow -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }
};


struct tri{
    int u, v, w;
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<vi> m(n, vi(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> m[i][j];

    vector<tri> T;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
                if (m[i][j] && m[j][k] && m[k][i]){
                    T.push_back({i, j, k});
                }

    dinic<double> graph(2 + T.size() + n);

    for (int i = 0; i < n; ++i)
        graph.add_edge(2 + T.size() + i, 1, 0.);

    for (int i = 0; i < (int)T.size(); ++i){
        graph.add_edge(0, 2 + i, 1.);

        graph.add_edge(2 + i, T[i].u + 2 + T.size(), 1.);
        graph.add_edge(2 + i, T[i].v + 2 + T.size(), 1.);
        graph.add_edge(2 + i, T[i].w + 2 + T.size(), 1.);
    }

    double lo = 0, hi = 1. + T.size();

    for (int i = 0; i < 200; ++i){
        double m = (lo + hi) / 2;
        graph.reset(m);

        double value = graph.max_flow(0, 1);
        double real_value = 1. * T.size() - value;

        if (real_value < eps)
            hi = m;
        else
            lo = m;
    }

    graph.reset(lo);
    double ans = graph.max_flow(0, 1);

    vector<int> answer;

    for (int i = 0; i < n; ++i){
        if (graph.side_of_S(2 + T.size() + i))
            answer.push_back(i + 1);
    }

    cout << answer.size() << endl;
    for (auto x : answer)
        cout << x << " ";
    cout << endl;

    return 0;
}