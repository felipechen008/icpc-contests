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
    int n, m;
    cin>>n>>m;
    vector<lint>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<lint>dp(m + 1, -linf);
    dp[0] = 0;
    for(int i=0;i<n;i++){
        for(int j=m-1;j>=0;j--) dp[j+1] = max(dp[j+1], dp[j] + a[i] * (j + 1));
    }
    cout<<dp[m]<<"\n";
    return 0;
}
