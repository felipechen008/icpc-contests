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
    int q;
    cin>>q;
    while(q--){
        string t;
        cin>>t;
        int n;
        cin>>n;
        vector<string>s(n);
        for(int i=0;i<n;i++) cin>>s[i];
        int m = int(size(t));
        vector<int>dp(m + 1, inf);
        vector<pair<int, int>>par(m+1);
        dp[0] = 0;
        par[0] = {-1, -1};
        for(int i=0;i<m;i++){
            for(int k=0;k<n;k++){
                int sz = int(size(s[k]));
                if(i + sz <= m && t.substr(i, sz) == s[k]){
                    for(int l=1;l<=sz;l++){
                        if(dp[i+l] > dp[i] + 1){
                            dp[i+l] = dp[i] + 1;
                            par[i+l] = {i, k};
                        }
                    }
                }
            }
        }
        if(dp[m] == inf) cout<<"-1\n";
        else{
            cout<<dp[m]<<"\n";
            vector<pair<int, int>>ans;
            int i = m;
            while(i){
                auto [x, y] = par[i];
                ans.emplace_back(x, y);
                i = x;
            }
            reverse(ans.begin(), ans.end());
            for(auto [x, y] : ans) cout<<y+1<<" "<<x+1<<"\n";
        }
    }
    return 0;
}
