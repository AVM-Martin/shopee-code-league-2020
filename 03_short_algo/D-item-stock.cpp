#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e5;

struct Data {
    int parent;
    int type;
    int qty;
    int stock;

    vector<int> adjList;
    int lazy;
};

Data dat[N+5];
int cnt[N+5];

int dfs(int u) {
    if (u == 1) {
        dat[u].stock -= dat[u].lazy;
    } else if (dat[u].type == 1) {
        dat[u].stock = dat[dat[u].parent].stock / dat[u].qty;
    }

    for (int v: dat[u].adjList) {
        dfs(v);
    }
    return 0;
}

int main() {
    dat[1].adjList.clear();
    dat[1].lazy = 0;

    int n,m; scanf("%d %d", &n, &dat[1].stock);
    for (int i=2; i<=n; i++) {
        scanf("%d %d %d", &dat[i].type, &dat[i].parent, &dat[i].qty);
        if (dat[i].type == 2) scanf("%d", &dat[i].stock);

        dat[dat[i].parent].adjList.push_back(i);
        dat[i].adjList.clear();
        dat[i].lazy = 0;
    }

    queue<int> kahn; while (!kahn.empty()) kahn.pop();
    for (int i=1; i<=n; i++) {
        cnt[i] = (int)dat[i].adjList.size();
        if (cnt[i] == 0) kahn.push(i);
    }

    while (!kahn.empty()) {
        int idx = kahn.front(); kahn.pop();
        if (idx == 1) continue;

        int par = dat[idx].parent;

        if (dat[idx].type == 1) {
            dat[par].lazy += dat[idx].lazy * dat[idx].qty;
            dat[idx].lazy = 0;

        } else if (dat[idx].type == 2) {
            dat[par].lazy += dat[idx].stock * dat[idx].qty;
            dat[idx].stock -= dat[idx].lazy;
            dat[idx].lazy = 0;
        }

        if (--cnt[par] == 0) {
            kahn.push(par);
        }
    }

    dfs(1);

    for (int i=1; i<=n; i++) {
        printf("%d\n", dat[i].stock);
    }
    return 0;
}
