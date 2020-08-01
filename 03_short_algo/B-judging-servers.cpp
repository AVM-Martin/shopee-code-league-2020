#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e3;
const ll INF = 1e17;

int tc;
int n,s;

ll li[N+5];
ll memo[N+5][N+5];

ll dp(int x, int y){
    if(y == 0) return 0;
    if(x > n) return INF;
    ll &ret = memo[x][y];
    if(ret != -1) return ret;
    ret = INF;
    //skip
    ret = min(ret,dp(x+1,y));
    //ambil 1
    ret = min(ret,dp(x+1,y-1)+li[x]);
    //ambil 2
    if(x+1 <= n) ret = min(ret,dp(x+2,y-2) + min(li[x] , li[x+1]));
    return ret;
}


int main(){
    scanf("%d",&tc);
    for(int tc_i=1;tc_i<=tc;tc_i++){
        memset(memo,-1,sizeof(memo));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++){
            scanf("%lld",&li[i]);
        }
        ll ans = dp(1,s);
        printf("Case %d: %lld\n",tc_i,ans);
    }
    return 0;
}
