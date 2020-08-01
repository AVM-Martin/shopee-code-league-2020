#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e5;
const long long INF = (long long)1e18;

vector< pair<int,int> > adjList[N+5];
long long dist[N+5][2];

int traverse(int n, int root, int idx) {
    for (int i=0; i<N+3; i++) {
        dist[i][idx] = INF;
    }

    pair<int, long long> res = make_pair(0, 0);

    queue< pair<int,long long> > bfs; while (!bfs.empty()) bfs.pop();
    bfs.push(make_pair(root, 0));

    while (!bfs.empty()) {
        int u = bfs.front().first;
        long long cost = bfs.front().second;
        bfs.pop();

        if (dist[u][idx] <= cost) continue;
        dist[u][idx] = cost;

        if (cost > res.second) {
            res = make_pair(u, cost);
        }

        // move
        for (pair<int,int> v: adjList[u]) {
            bfs.push(make_pair(v.first, cost + v.second));
        }
    }

    return res.first;
}

int main() {
    for (int i=0; i<N+3; i++) {
        adjList[i].clear();
    }

    int n; scanf("%d", &n);
    for (int i=1; i<=n-1; i++) {
        int u,v,w; scanf("%d %d %d", &u, &v, &w);
        adjList[u].push_back(make_pair(v,w));
        adjList[v].push_back(make_pair(u,w));
    }

    int root_a = traverse(n, traverse(n,1,0), 0);
    int root_b = traverse(n, root_a, 1);

    pair<int, long long> res = make_pair(0,0);
    for (int i=1; i<=n; i++) {
        if (i != root_a && dist[i][0] > res.second) {
            res = make_pair(i, dist[i][0]);
        }
        if (i != root_b && dist[i][1] > res.second) {
            res = make_pair(i, dist[i][1]);
        }
    }

    printf("%lld\n", res.second);
    return 0;
}
