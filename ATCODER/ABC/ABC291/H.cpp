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

    vector<int>sz(n);
    vector<bool>vis(n);
    auto dfs = [&](auto& self, int u, int p)->void {
        sz[u] = 1;
        for(int v : g[u]){
            if(v == p || vis[v]) continue;
            self(self, v, u);
            sz[u] += sz[v];
        }
    };


    auto find_centroid = [&](int u)->int {
        dfs(dfs, u, u);
        int p = -1, cursz = sz[u];
        do {
            int nxt = -1;
            for(int v : g[u]) {
                if(v != p && !vis[v] && 2 * sz[v] > cursz) nxt = v;
            }
            p = u, u = nxt;
        } while(u != -1);
        return p;
    };

    vector<int>ans(n);

    auto centroid_decomp = [&](auto& self, int u, int p)->void {
        int centroid = find_centroid(u);
        vis[centroid] = 1;
        ans[centroid] = p;
        for(int v : g[centroid]){
            if(vis[v]) continue;
            self(self, v, centroid);
        }
    };

    centroid_decomp(centroid_decomp, 0, -2);

    for(int u : ans) cout<<u + 1<<" ";
    cout<<"\n";


    return 0;
}
