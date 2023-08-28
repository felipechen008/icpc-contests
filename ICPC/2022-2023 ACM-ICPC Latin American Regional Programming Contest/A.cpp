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
    vector<vector<int>>g(n), h(n);
    for(int i=0;i<n;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[i].push_back(a);
        g[i].push_back(b);
        h[a].push_back(i);
        h[b].push_back(i);
    }
    for(int i=0;i<n;i++){
        int a = g[i][0], b = g[i][1];
        vector<bool>vis(n);
        vector<int>cnt(n);
        auto dfs = [&](auto& self, int u)->void {
            vis[u] = 1;
            for(int v : h[u]){
                if(vis[v] || ( (u == a || u == b) && v == i) ) continue;
                self(self, v);
            }
        };
        dfs(dfs, a);
        for(int j=0;j<n;j++) cnt[j] += vis[j], vis[j] = 0;
        dfs(dfs, b);
        for(int j=0;j<n;j++) cnt[j] += vis[j], vis[j] = 0;
        dfs(dfs, i);
        for(int j=0;j<n;j++) cnt[j] += vis[j], vis[j] = 0;
        int ans = 0;
        for(int j=0;j<n;j++) ans += cnt[j] == 3;
        if(ans) cout<<"Y";
        else cout<<"N";
    }
    cout<<"\n";
    return 0;
}
