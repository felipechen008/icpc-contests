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
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    lint ans = 0;
    for(int i=1;i<=n;i++){
        vector dp(n+1, vector(i+2, vector(i, lint(0))));
        dp[0][0][0] = 1;
        for(int j=0;j<n;j++){
            for(int k=0;k<=i;k++){
                for(int l=0;l<i;l++){
                    dp[j+1][k][l] = (dp[j+1][k][l] + dp[j][k][l])%mod;
                    dp[j+1][k+1][(l+a[j])%i] = (dp[j+1][k+1][(l+a[j])%i] + dp[j][k][l])%mod;
                }
            }
        }
        ans = (ans + dp[n][i][0]) % mod;
    }
    cout<<ans<<"\n";
    return 0;
}
