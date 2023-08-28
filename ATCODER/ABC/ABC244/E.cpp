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
    int n, m, k, s, t, x;
    cin>>n>>m>>k>>s>>t>>x;
    s--, t--, x--;
    vector<pair<int, int>>e(m);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        e[i] = {a, b};
    }
    vector<array<lint, 2>>dp(n);
    dp[s][0] = 1;
    for(int i=0;i<k;i++){
        vector<array<lint, 2>>ndp(n);
        for(auto [a, b] : e){
            for(int j=0;j<2;j++){
                if(b == x) ndp[b][j^1] = (ndp[b][j^1] + dp[a][j]) % mod;
                else ndp[b][j] = (ndp[b][j] + dp[a][j]) % mod;
                if(a == x) ndp[a][j^1] = (ndp[a][j^1] + dp[b][j]) % mod;
                else ndp[a][j] = (ndp[a][j] + dp[b][j]) % mod;
            }
        }
        swap(dp, ndp);
    }
    cout<<dp[t][0]<<"\n";
    return 0;
}
