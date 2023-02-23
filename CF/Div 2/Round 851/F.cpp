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
    int n, q;
    cin>>n>>q;
    vector<vector<pair<int, int>>>g(n);
    for(int i=0;i<n-1;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }
    vector<array<int, 3>>query(q);
    for(int i=0;i<q;i++){
        int a, b, x;
        cin>>a>>b>>x;
        a--, b--;
        query[i] = {a, b, x};
    }

    vector<vector<pair<int, int>>>h(n);
    for(auto [u, v, x] : query){
        h[u].emplace_back(v, x);
        h[v].emplace_back(u, x);
    }
    bool ok = true;
    vector<bool>vis(n);
    vector<int>cur, dp(n), ans(n-1);

    auto dfs = [&](auto& self, int u)->void {
        vis[u] = 1;
        cur.emplace_back(u);
        for(auto [v, x] : h[u]){
            if(vis[v]){
                if(dp[u] != (dp[v] ^ x)) ok = false;
                continue;
            }
            dp[v] = dp[u] ^ x;
            self(self, v);       
        }
    };

    vector<int>odd;
    int cnt = 0;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            cur.clear();
            dfs(dfs, i);
            if(i){
                int o = 0;
                for(int u : cur) if(size(g[u])&1) o++;
                if(o&1) swap(odd, cur);
            }
        }
        if(size(g[i])&1) cnt ^= dp[i];
    }

    if(!ok){
        cout<<"No\n";
        return 0;
    }

    for(int u : odd) dp[u] ^= cnt;

    auto calc = [&](auto& self, int u, int p)->void {
        for(auto [v, e] : g[u]){
            if(v == p) continue;
            ans[e] = dp[u] ^ dp[v];
            self(self, v, u);
        }
    };

    calc(calc, 0, 0);

    cout<<"Yes\n";
    for(int u : ans) cout<<u<<" ";
    cout<<"\n";


    return 0;
}
