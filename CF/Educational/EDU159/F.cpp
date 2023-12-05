#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int lg = 20;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<vector<int>>g(n);
    for(int i=1;i<n;i++){
        int x, y;
        cin>>x>>y;
        x--, y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int q;
    cin>>q;
    vector<array<int, 3>>query(q);
    for(int i=0;i<q;i++){
        int x, y, k;
        cin>>x>>y>>k;
        x--, y--;
        query[i] = {x, y, k};
    }

    vector<bool>vis(n);
    vector<int>sz(n);

    auto calc = [&](auto& self, int u, int p)->void {
        sz[u] = 1;
        for(int v : g[u]){
            if(v == p || vis[v]) continue;
            self(self, v, u);
            sz[u] += sz[v];
        }
    };

    auto find_centroid = [&](auto& self, int u, int p, int cursz)->int {
        for(int v : g[u]){
            if(v != p && !vis[v] && 2 * sz[v] > cursz)
                return self(self, v, u, cursz);
        }
        return u;
    };

    vector<vector<int>>memo(n);
    {
        vector<int>parents(n), h(n);
        calc(calc, 0, 0);
        int root = find_centroid(find_centroid, 0, 0, sz[0]);
        parents[root] = -1;
        auto comp_parents = [&](auto& self, int u)->void {
            vis[u] = 1;
            for(int v : g[u]){
                if(vis[v]) continue;
                calc(calc, v, u);
                int centroid = find_centroid(find_centroid, v, u, sz[v]);
                h[centroid] = h[u] + 1;
                parents[centroid] = u;
                self(self, centroid);
            }
        };
        comp_parents(comp_parents, root);

        for(int i=0;i<n;i++) vis[i] = 0;
        for(int i=0;i<q;i++){
            auto [x, y, k] = query[i];
            while(x != y){
                if(h[x] > h[y]) x = parents[x];
                else y = parents[y];
            }
            memo[x].push_back(i);
        }
    }
    vector<int>base_cur(lg, -1);
    vector<vector<int>>bases(n, base_cur);
    auto dfs = [&](auto& self, int u, int p)->void {
        int aux = a[u], ind = -1;
        for(int b=lg-1;b>=0;b--){
            if(aux>>b&1){
                if(base_cur[b] == -1) base_cur[b] = aux, ind = b;
                aux ^= base_cur[b];
            }
        }
        bases[u] = base_cur;
        for(int v : g[u]){
            if(v == p || vis[v]) continue;
            self(self, v, u);
        }
        if(ind != -1) base_cur[ind] = -1;
    };
    vector<bool>ans(q);

    auto solve = [&](auto& self, int u)->void {
        calc(calc, u, u);
        int centroid = find_centroid(find_centroid, u, u, sz[u]);
        vis[centroid] = 1;
        dfs(dfs, centroid, centroid);
        for(int i : memo[centroid]){
            auto [x, y, k] = query[i];
            vector<int>cur = bases[x];
            for(int val : bases[y]){
                if(val == -1) continue;
                for(int b=lg-1;b>=0;b--){
                    if(val>>b&1){
                        if(cur[b] == -1) cur[b] = val;
                        val ^= cur[b];
                    }
                }
            }
            for(int b=lg-1;b>=0;b--){
                if(k>>b&1){
                    if(cur[b] != -1) k ^= cur[b];
                }
            }
            if(!k) ans[i] = 1; 
        }

        for(int v : g[centroid]){
            if(vis[v]) continue;
            self(self, v);
        }
    };

    solve(solve, 0);
    for(int i=0;i<q;i++){
        if(ans[i]) cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}
