#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,
            tree_order_statistics_node_update>;

typedef pair<long long, long long> pll;
typedef pair<pll, int> tup;

const int N = (int)1e5;

long long get_dist2(pll a, pll b) {
    long long reta = (a.first - b.first) * (a.first - b.first);
    long long retb = (a.second - b.second) * (a.second - b.second);
    return reta + retb;
}
int cmpp(tup a, tup b) {
    if (a.first.first != b.first.first) {
        return a.first.first < b.first.first;
    } else {
        return a.second < b.second;
    }
}

pll dat[N+5];
pll que[N+5];
vector<tup> order;

Tree<pll> ds;
Tree<pll> dst;

int res[N+5];

int main() {
    ds.clear();
    dst.clear();
    order.clear();

    int n; scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%lld %lld", &dat[i].first, &dat[i].second);
    }

    pll a; scanf("%lld %lld", &a.first, &a.second);
    pll b; scanf("%lld %lld", &b.first, &b.second);

    int q; scanf("%d", &q);
    for (int qq=1; qq<=q; qq++) {
        scanf("%lld %lld", &que[qq].first, &que[qq].second);
        que[qq].first *= que[qq].first;
        que[qq].second *= que[qq].second;
        order.push_back(make_pair(que[qq], qq));
    }

    // compare
    for (int i=1; i<=n; i++) {
        long long reta = get_dist2(dat[i], a);
        long long retb = get_dist2(dat[i], b);

        dst.insert(make_pair(retb, -i));

        order.push_back(make_pair(make_pair(reta, retb), -i));
    }

    sort(order.begin(), order.end(), cmpp);

    // do
    for (tup x: order) {
        if (x.second < 0) {
            ds.insert(make_pair(x.first.second, x.second));
        } else {
            int reta = ds.size();
            int retb = dst.order_of_key(make_pair(x.first.second, 0));
            int rett = ds.order_of_key(make_pair(x.first.second, 0));
            res[x.second] = n - (reta + retb - 2 * rett);
        }
    }

    // print
    for (int qq=1; qq<=q; qq++) {
        printf("%d\n", res[qq]);
    }
    return 0;
}
