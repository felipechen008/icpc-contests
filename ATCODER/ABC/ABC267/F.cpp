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
    vector<int>h(n), par(n);
    auto dfs = [&](auto& self, int u, int p)->void {
        par[u] = p;
        for(int v : g[u]){
            if(v == p) continue;
            h[v] = h[u] + 1;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);
    int root = 0;
    for(int i=0;i<n;i++) if(h[i] > h[root]) root = i;
    dfs(dfs, root, root);
    int other = 0;
    for(int i=0;i<n;i++) if(h[i] > h[other]) other = i;
    vector<vector<int>>anc(18, vector<int>(n));
    anc[0] = par;
    dfs(dfs, other, other);
    vector<vector<int>>anc2(18, vector<int>(n));
    anc2[0] = par;
    for(int b=1;b<18;b++){
        for(int i=0;i<n;i++) anc[b][i] = anc[b-1][anc[b-1][i]];
    }
    for(int b=1;b<18;b++){
        for(int i=0;i<n;i++) anc2[b][i] = anc2[b-1][anc2[b-1][i]];
    }
    auto get_anc = [&](int u, int k)->int {
        for(int b=17;b>=0;b--) if(k>>b&1) u = anc[b][u];
        return u;
    };
    auto get_anc2 = [&](int u, int k)->int {
        for(int b=17;b>=0;b--) if(k>>b&1) u = anc2[b][u];
        return u;
    };
    int q;
    cin>>q;
    while(q--){
        int u, k;
        cin>>u>>k;
        u--;
        if(get_anc(u, k-1) != root) cout<<get_anc(u, k) + 1<<"\n"; 
        else if(get_anc2(u, k-1) != other) cout<<get_anc2(u, k) + 1<<"\n";
        else cout<<"-1\n";
    }
    return 0;
}
