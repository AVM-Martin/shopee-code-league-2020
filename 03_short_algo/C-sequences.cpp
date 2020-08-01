#include <bits/stdc++.h>
using namespace std;

const int N = (int)5e3;
const int K = (int)2e3;
const long long MOD = (long long)1e9 + 7;

int dat[N+5][3];
long long cnt[K+5];

vector<long long> combine(vector<long long> a, vector<long long> b, int k) {
    vector<long long> res; res.clear();
    for (int i=0; i<k; i++) res.push_back(0);

    for (int i=0; i<k; i++) {
        for (int j=0; j<k; j++) {
            res[(i+j) % k] = (res[(i+j) % k] + ((a[i] * b[j]) % MOD)) % MOD;
        }
    }

    return res;
}

vector<long long> fast(int m, int k) {
    vector<long long> res; res.clear();
    for (int i=0; i<k; i++) res.push_back(0);

    if (m == 0) {
        res[0] = 0;
        return res;
    } else if (m == 1) {
        for (int i=0; i<k; i++) {
            res[i] = cnt[i] % MOD;
        }
        return res;
    }

    res = fast(m >> 1, k);
    res = combine(res, res, k);
    if (m & 1) res = combine(res, fast(1,k), k);
    return res;
}

int main() {
    int n,m,k; scanf("%d %d %d", &n, &m, &k);
    for (int i=1; i<=n; i++) {
        scanf("%d %d %d", &dat[i][0], &dat[i][1], &dat[i][2]);
    }

    for (int i=1; i<=n; i++) {
        const int a = dat[i][0];
        const int b = dat[i][1];
        const int c = dat[i][2];

        int bats = min(c, k);
        int mods = c % k;

        for (int j=1; j<=bats; j++) {
            int idx = (j * j) % k;
            idx = ((a * idx) + b) % k;

            int _cnt = (c / k) + (j <= (c % k));
            cnt[idx] = (cnt[idx] + (long long)_cnt) % MOD;
        }
    }

    vector<long long> res = fast(m, k);
    printf("%lld\n", res[0] % MOD);
    return 0;
}
