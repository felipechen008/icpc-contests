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
    vector<vector<int>>g(n);
    for(int i=1;i<n;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int>h(n);
    vector<vector<int>>anc(18, vector<int>(n));
    vector<lint>dp(n), cnt(n);

    auto dfs = [&](auto& self, int u, int p)->void {
        anc[0][u] = p;
        cnt[u] = 1;
        for(int v : g[u]){
            if(v == p) continue;
            h[v] = h[u] + 1;
            self(self, v, u);
            dp[u] += dp[v] + cnt[v];
            cnt[u] += cnt[v];
        }
    };

    dfs(dfs, 0, 0);

    for(int b=1;b<18;b++){
        for(int i=0;i<n;i++){
            anc[b][i] = anc[b-1][anc[b-1][i]];
        }
    }

    auto get_lca = [&](int u, int v)->int {
        if(h[u] < h[v]) swap(u, v);
        int d = h[u] - h[v];
        for(int b=17;b>=0;b--) if(d>>b&1) u = anc[b][u];
        for(int b=17;b>=0;b--) if(anc[b][u] != anc[b][v]) u = anc[b][u], v = anc[b][v];
        if(u != v) u = anc[0][u];
        return u;
    };

    auto get_dist = [&](int u, int v)->int {
        int lca = get_lca(u, v);
        return h[u] + h[v] - 2 * h[lca];
    };


    int q;
    cin>>q;
    vector<vector<array<int, 3>>>query(n);
    vector<vector<int>>query2(n);

    for(int i=0;i<q;i++){
        int u, v;
        cin>>u>>v;
        u--, v--;
        if(u != v){
            if(h[u] < h[v]) swap(u, v);
            int d = get_dist(u, v);
            int mid = u;
            int du = (d - 1) / 2, dv = d / 2;
            for(int b=17;b>=0;b--) if(du>>b&1) mid = anc[b][mid];
            query[u].push_back({anc[0][mid], du + 1, i});
            query[v].push_back({mid, dv + 1, i});
        }
        else{
            query2[u].push_back(i);
        }
    }


    vector<lint>ans(q);

    auto reroot = [&](auto& self, int u, int p)->void {
        for(auto [v, d, i] : query[u]) ans[i] += dp[u] - dp[v] - cnt[v] * d;
        for(int i : query2[u]) ans[i] = dp[u];

        for(int v : g[u]){
            if(v == p) continue;

            dp[u] -= dp[v] + cnt[v];
            cnt[u] -= cnt[v];

            dp[v] += dp[u] + cnt[u];
            cnt[v] += cnt[u];

            self(self, v, u);

            dp[v] -= dp[u] + cnt[u];
            cnt[v] -= cnt[u];

            dp[u] += dp[v] + cnt[v];
            cnt[u] += cnt[v];
        }
    };

    reroot(reroot, 0, 0);
    for(int i=0;i<q;i++) cout<<ans[i]<<"\n";



    return 0;
}
