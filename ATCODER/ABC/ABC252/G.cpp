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
    vector<int>p(n);
    for(int i=0;i<n;i++) cin>>p[i];
    vector<vector<lint>>dp(n, vector<lint>(n));
    vector<vector<bool>>vis(n, vector<bool>(n));

    auto solve = [&](auto& self, int l, int r)->lint {
        if(l >= r) return 1;
        if(vis[l][r]) return dp[l][r];
        vis[l][r] = 1;
        lint& c = dp[l][r];
        for(int k=l+1;k<=r;k++){
            if(p[k] > p[l]){
                c = (c + self(self, l+1, k-1) * self(self, k, r)) % mod;
            }
        }
        c = (c + self(self, l+1, r)) % mod;
        return c;
    };
    cout<<solve(solve, 1, n-1)<<"\n";

    return 0;
}
