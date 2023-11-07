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
    int n, m, k;
    cin>>n>>m>>k;
    if(!k){
        lint ans = 1;
        for(int i=0;i<n;i++) ans = ans * m % mod;
        cout<<ans<<"\n";
        return 0;
    }
    vector<lint>dp(m, 1), pref(m + 1);
    for(int i=1;i<=m;i++) pref[i] = i;
    for(int i=1;i<n;i++){
        for(int j=0;j<m;j++){
            int l1 = 0, r1 = max(-1, j - k);
            int l2 = min(m, j + k), r2 = m - 1;
            dp[j] = pref[r1 + 1] - pref[l1] +
                pref[r2 + 1] - pref[l2];
            dp[j] = (dp[j] % mod + mod) % mod;
        }
        for(int j=0;j<m;j++) pref[j+1] = (pref[j] + dp[j]) % mod;
    }
    cout<<pref[m]<<"\n";

    return 0;
}
