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
    vector<int>x(n);
    for(int i=0;i<n;i++) cin>>x[i];
    vector<int>c(m), y(m);
    for(int i=0;i<m;i++) cin>>c[i]>>y[i];
    vector<lint>pref(n + 1), pref2(n + 1);
    for(int i=0;i<n;i++) pref[i+1] = x[i];
    for(int i=0;i<n;i++) pref[i+1] += pref[i];
    for(int i=0;i<m;i++) pref2[c[i]] += y[i];
    for(int i=0;i<n;i++) pref2[i+1] += pref2[i];
    vector<lint>dp(n + 2);
    for(int i=0;i<=n;i++){
        for(int j=0;i+j<=n;j++){
            dp[i+j+1] = max(dp[i+j+1], dp[i] + pref2[j] + pref[i+j] - pref[i]);
        }
    }
    cout<<dp[n + 1]<<"\n";

    return 0;
}
