/*
    Name:
        Fast Maximum Flow

    Test:
        graph/dinic.cpp

    Link:
        http://www.spoj.com/problems/FASTFLOW/

    Notes:
        Build undirected network flow using graph.add_edge(u, v, c0, c1)
        where c0 is the capacity of the edge (u, v) and c1 of the edge (v, u)
*/

#include <bits/stdc++.h>
#include <graph/dinic.hpp>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    dinic<int, long long> graph(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        graph.add_edge(u, v, c, c);
    }

    cout << graph.max_flow(0, n - 1) << endl;

    return 0;
}