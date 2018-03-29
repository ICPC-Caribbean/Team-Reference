/*
    Algorithm:
        Max Flow (Dinic)

    Complexity:
        O(n^2 * m)

    Tested:
        https://www.hackerrank.com/contests/w30/challenges/a-graph-problem/problem
        http://www.spoj.com/problems/FASTFLOW/

    Notes:
        + In practice is faster than O(n^2 * m)
        + For network where each edge has capacity 1 the complexity is O(m * min(m^(1/2), n^(2/3))
            Reference: https://people.orie.cornell.edu/dpw/orie633/LectureNotes/lecture9.pdf (Lemma 4)
*/

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
