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
        int n;
        cin>>n;
        vector<vector<int>>g(n);
        for(int i=0;i<n;i++){
            int a, b;
            cin>>a>>b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        
        bool ok = true;
        for(int i=0;i<n;i++) if(int(size(g[i])) > 2) ok = false;
        vector<bool>vis(n);
        int cnt = 0;
        auto dfs = [&](auto& self, int u)->void {
            vis[u] = 1;
            cnt++;
            for(int v : g[u]){
                if(vis[v]) continue;
                self(self, v);
            }
        };
        for(int i=0;i<n;i++){
            if(!vis[i]){
                cnt = 0;
                dfs(dfs, i);
                if(cnt&1) ok = false;
            }
        }
        if(ok) cout<<"YES\n";
        else cout<<"NO\n";


    }
    return 0;
}
