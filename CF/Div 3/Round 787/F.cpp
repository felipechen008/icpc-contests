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
    int t;
    cin>>t;
    while(t--){
        int n, k;
        cin>>n>>k;
        int x, y;
        cin>>x>>y;
        x--, y--;
        vector<int>a(k), ch(n);
        for(int i=0;i<k;i++) cin>>a[i], a[i]--, ch[a[i]] = 1;
        vector<vector<int>>g(n);
        for(int i=1;i<n;i++){
            int a, b;
            cin>>a>>b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<int>par(n);
        auto compute = [&](auto& self, int u, int p)->void {
            par[u] = p;
            for(int v : g[u]){
                if(v == p) continue;
                self(self, v, u);
                ch[u] += ch[v];
            }
        };
        compute(compute, x, x);
        vector<bool>path_to_y(n);
        {
            int z = y;
            while(z != x){
                path_to_y[z] = 1;
                z = par[z];
            }
        }

        int ans = 0;

        auto dfs = [&](auto& self, int u, int p)->void {
            int ind = -1;
            for(int v : g[u]){
                if(v == p) continue;
                if(path_to_y[v]){
                    ind = v;
                    continue;
                }
                if(ch[v]){
                    ans++;
                    self(self, v, u);
                    ans++;
                }
            }
            if(ind != -1){
                ans++;
                self(self, ind, u);
            }
        };
        dfs(dfs, x, x);
        cout<<ans<<"\n";

    }

    return 0;
}
