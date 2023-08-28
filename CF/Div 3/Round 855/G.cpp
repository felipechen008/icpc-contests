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
        for(int i=1;i<n;i++){
            int a, b;
            cin>>a>>b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<int>hashes(n), par(n);
        map<vector<int>, int> subtree;
        auto dfs = [&](auto& self, int u, int p)->void {
            vector<int>cur;
            par[u] = p;
            for(int v : g[u]){
                if(v == p) continue;
                self(self, v, u);
                cur.push_back(hashes[v]);
            }
            sort(cur.begin(), cur.end());
            if(!subtree.count(cur)) subtree[cur] = int(subtree.size());
            hashes[u] = subtree[cur];
        };
        
        dfs(dfs, 0, 0);

        vector<int>cnt(n+1);
        bool ok = true;
        int u = 0;
        while(ok){
            for(int v : g[u]) cnt[hashes[v]]++;
            int nxt = -1, odd = 0;
            for(int v : g[u]){
                if(v == par[u]) continue;
                if(cnt[hashes[v]]&1){
                    odd++;
                    nxt = v;
                    cnt[hashes[v]] = 0;
                }
            }
            if(odd > 1) ok = false; 
            else if(nxt == -1) break;
            else u = nxt;
        }

        if(ok) cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}
