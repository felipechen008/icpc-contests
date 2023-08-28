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
    int n, k;
    cin>>n>>k;
    vector<int>a(n), b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    vector dp(n, vector<bool>(2));
    dp[0][0] = dp[0][1] = 1;
    for(int i=1;i<n;i++){
        if(dp[i-1][0] && abs(a[i] - a[i-1]) <= k) dp[i][0] = 1;
        if(dp[i-1][0] && abs(b[i] - a[i-1]) <= k) dp[i][1] = 1;
        if(dp[i-1][1] && abs(a[i] - b[i-1]) <= k) dp[i][0] = 1;
        if(dp[i-1][1] && abs(b[i] - b[i-1]) <= k) dp[i][1] = 1;
    }
    if(dp[n-1][0] || dp[n-1][1]) cout<<"Yes\n";
    else cout<<"No\n";

    return 0;
}
