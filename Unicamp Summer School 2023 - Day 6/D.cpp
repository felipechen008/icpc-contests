#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int lim = 10010;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; lint h;
    cin>>n>>h;
    vector<lint>p(n);
    vector<int>v(n);
    for(int i=0;i<n;i++) cin>>p[i]>>v[i];
    vector<lint>dp(lim, -inf);
    dp[0] = 0;
    for(int i=0;i<n;i++){
        vector<lint>ndp(lim, -inf);
        for(int j=0;j<lim;j++){
            if(dp[j] == -inf) continue;
            lint cur = p[i];
            lint cnt = p[i];
            int k = v[i];
            ndp[j] = max(ndp[j], dp[j]);
            while(k){
                k >>= 1;
                ndp[j + (v[i] - k)] = max(ndp[j + (v[i] - k)], dp[j] + cnt );
                cur <<= 1;
                cnt += cur;
            }
        }
        swap(dp, ndp);
    }
    int ans = -1;
    for(int i=0;i<lim;i++) if(dp[i] >= h){ ans = i; break; }
    cout<<ans<<"\n";

    return 0;
}