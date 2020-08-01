#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e3;
const ll INF = 2e9+3;

bool cek_bit(int x, int mask){
    return (1<<x) & mask;
}

int tog_bit(int x, int mask){
    return (1<<x) ^ mask;
}

int n,k;
ll li[N+5][5];
ll memo[N][3][(1<<3)][N];

ll dp(int r, int c, int mask, int sisa){
    if(sisa < 0) return -INF;
    if(c == 3) return dp(r+1,0,mask,sisa);
    if(r == n){
        if(sisa == 0) return 0;
        return -INF;
    }
    ll &ret = memo[r][c][mask][sisa];
    if(ret != -INF-2) return ret;
    //skip
    ret = dp(r,c+1,mask/2,sisa);
    //ambil atas
    if(!cek_bit(0,mask) && r != 0) ret = max(ret,dp(r,c+1,tog_bit(0,tog_bit(3,mask))/2,sisa-1) + li[r][c] + li[r-1][c]);
    //ambil kiri
    if(!cek_bit(2,mask) && c != 0) ret = max(ret,dp(r,c+1,tog_bit(2,tog_bit(3,mask))/2 , sisa-1) + li[r][c] + li[r][c-1]);
    return ret;
}

void bt(int r, int c, int mask, int sisa){
    if(c == 3) return bt(r+1,0,mask,sisa);
    if(r == n){
        return;
    }
    //skip
    if(dp(r,c+1,mask/2,sisa) == dp(r,c,mask,sisa)) {
        bt(r,c+1,mask/2,sisa);
        return;
    }
    //ambil atas
    if(!cek_bit(0,mask) && r != 0 && dp(r,c+1,tog_bit(0,tog_bit(3,mask))/2,sisa-1) + li[r][c] + li[r-1][c] == dp(r,c,mask,sisa)){
        bt(r,c+1,tog_bit(0,tog_bit(3,mask))/2,sisa-1);
        printf("PICK %d,%d keatas\n",r,c);
        return;
    }
    //ambil kiri
    if(!cek_bit(2,mask) && c != 0 && dp(r,c+1,tog_bit(2,tog_bit(3,mask))/2 , sisa-1) + li[r][c] + li[r][c-1] == dp(r,c,mask,sisa)){
        bt(r,c+1,tog_bit(2,tog_bit(3,mask))/2 , sisa-1);
        printf("PICK %d,%d kekiri\n",r,c);
    }
    return;
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            scanf("%lld",&li[i][j]);
        }
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<3;j++){
            for(int l=0;l<(1<<3);l++){
                for(int m=0;m<N;m++){
                    memo[i][j][l][m] = -INF-2;
                }
            }
        }
    }

    ll ans = dp(0,0,0,k);
//  bt(0,0,0,k);
    printf("%lld\n",ans);
    return 0;
}
