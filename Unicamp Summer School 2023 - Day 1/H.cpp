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
    vector<int>f(12);
    int sum = 0;
    for(int i=0;i<n;i++) cin>>f[i], sum += (i+1) * f[i];
    if(sum > 78){
        cout<<"impossible\n";
        return 0;
    }
    vector<int>pref(13);
    pref[0] = 1;
    for(int i=1;i<=n;i++) pref[i] = pref[i-1] * (f[i-1] + 1);

    vector<pair<int, int>>dp(pref[n], {13, 0});
    dp[0] = {0, 0};
    for(int hash=0;hash<pref[n];hash++){
        vector<int>a(n);
        int cur = hash;
        for(int i=0;i<n;i++){
            a[i] = cur % (f[i] + 1);
            cur /= (f[i] + 1);
        }
        auto [x, y] = dp[hash];
        for(int i=0;i<n;i++){
            if(a[i] == f[i]) continue;
            int nhash = hash + pref[i];
            if(x < i + 1) dp[nhash] = min(dp[nhash], {i+1, i+1});
            else{
                if(y + i + 2 > x) dp[nhash] = min(dp[nhash], {x+1, i+1});
                else dp[nhash] = min(dp[nhash], {x, y+i+2});
            }
        }
    }
    if(dp[pref[n] - 1].first > 12) cout<<"impossible\n";
    else cout<<dp[pref[n] - 1].first<<"\n";

    
    return 0;
}
