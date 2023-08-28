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
    vector<int>a(n), b(n);
    for(int i=0;i<n;i++) cin>>a[i]>>b[i];
    vector<array<lint, 2>>dp(n);
    dp[0][0] = dp[0][1] = 1;
    for(int i=1;i<n;i++){
        if(a[i] != a[i-1]) dp[i][0] += dp[i-1][0];
        if(a[i] != b[i-1]) dp[i][0] += dp[i-1][1];
        if(b[i] != a[i-1]) dp[i][1] += dp[i-1][0];
        if(b[i] != b[i-1]) dp[i][1] += dp[i-1][1];
        dp[i][0] %= mod;
        dp[i][1] %= mod;
    }
    lint ans = (dp[n-1][0] + dp[n-1][1]) % mod;

    cout<<ans<<"\n";

    return 0;
}
