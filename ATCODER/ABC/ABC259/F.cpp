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
    vector<int>d(n);
    for(int i=0;i<n;i++) cin>>d[i];
    vector<vector<pair<int, int>>>g(n);
    for(int i=1;i<n;i++){
        int a, b, c;
        cin>>a>>b>>c;
        a--, b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    vector<array<lint, 2>>dp(n);
    auto dfs = [&](auto& self, int u, int p)->void {
        vector<lint>cur;
        lint cnt = 0;
        for(auto [v, c] : g[u]){
            if(v == p) continue;
            self(self, v, u);
            if(d[v] && c + dp[v][0] - dp[v][1] > 0) 
                cur.push_back(c + dp[v][0] - dp[v][1]);
            cnt += dp[v][1];
        }
        sort(cur.rbegin(), cur.rend());
        for(int i=0;i<(int)cur.size() && i<d[u]-1;i++){
            cnt += cur[i];
        }
        dp[u][0] = cnt;
        if(d[u] && d[u] <= (int)cur.size()) cnt += cur[d[u]-1];
        dp[u][1] = cnt;
    };
    dfs(dfs, 0, 0);
    cout<<max(dp[0][0], dp[0][1])<<"\n";
    
    return 0;
}
