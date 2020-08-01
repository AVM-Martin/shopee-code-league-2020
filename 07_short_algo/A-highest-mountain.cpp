#include <bits/stdc++.h>
using namespace std;

const int N = 1e3;

int main() {
    int tc, n, arr[N+10];

    scanf("%d", &tc);
    for (int t = 1; t <= tc; ++t) {
        int l=-1, len=-1, peak=-1;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
        for (int i = 0; i < n; ++i) {
            if (arr[i] == 1 && l != 1) {
                l = 1;
            } else if (arr[i] == l+1) {
                l++;
            } else if (len < l) {
                len = l;
                peak = i-1;
                l = -1;
            }
        }
        if (len < l) {
            len = l;
            peak = n-1;
        }

        for (int i = n-1; i >= 0; --i) {
            if (arr[i] == 1 && l != 1) {
                l = 1;
            } else if (arr[i] == l+1) {
                l++;
            } else if (len < l) {
                len = l;
                peak = i+1;
                l = -1;
            }
        }

        if (len < l) {
            len = l;
            peak = 0;
        }

        printf("Case #%d: %d %d\n", t, len, peak);
    }
    return 0;
}
