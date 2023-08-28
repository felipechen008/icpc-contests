#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, t;
    cin>>n>>m>>t;
    vector<vector<lint>>v(n, vector<lint>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>v[i][j];
    }

    vector sum(n, vector(m, vector(n, vector(m, lint(0)))));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            vector<lint>cnt(m);
            for(int k=i;k<n;k++){
                lint cur = 0;
                for(int l=j;l<m;l++){
                    cur += v[k][l];
                    cnt[l] += cur;
                    sum[i][j][k][l] = cnt[l];
                }
            }
        }
    }

    auto solve = [&](lint x)->lint {
        lint lo = 0, hi = 1e18;
        while(lo <= hi){
            lint mid = (lo + hi) / 2;
            vector dp(n, vector(m, vector(n, vector(m, lint(0)))));
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    for(int k=i;k<n;k++){
                        for(int l=j;l<m;l++){
                            if(sum[i][j][k][l] >= x && sum[i][j][k][l] <= x + mid){
                                dp[i][j][k][l] = 2;
                            }
                        }
                    }
                }
            }
            for(int a=0;a<n;a++){
                for(int b=0;b<m;b++){
                    for(int i=0;i+a<n;i++){
                        for(int j=0;j+b<m;j++){
                            int k = i + a, l = j + b;
                            for(int c=0;c<a;c++){
                                for(int bits=0;bits<=t;bits++){
                                    if(dp[i][j][i+c][l]>>bits&1){
                                        dp[i][j][k][l] |= dp[i+c+1][j][k][l]<<bits;
                                    }
                                }
                            }
                            for(int c=0;c<b;c++){
                                for(int bits=0;bits<=t;bits++){
                                    if(dp[i][j][k][j+c]>>bits&1){
                                        dp[i][j][k][l] |= dp[i][j+c+1][k][l]<<bits;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if( (dp[0][0][n-1][m-1]>>(t+1))&1 ) hi = mid - 1;
            else lo = mid + 1;
        }
        return lo;
    };
    lint ans = linf;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=i;k<n;k++){
                for(int l=j;l<m;l++){
                    ans = min(ans, solve(sum[i][j][k][l]));
                }
            }
        }
    }
    cout<<ans<<"\n";

    

    return 0;
}
