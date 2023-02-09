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
    vector<int>f(n), h(n);
    for(int i=0;i<n;i++) cin>>f[i]>>h[i];
    
    {
        // 1 color
        int fired = 0;
        for(int i=0;i<n;i++) fired += f[i] > 0;
        if(!fired){
            cout<<"1\n";
            for(int i=0;i<n;i++) cout<<"1 ";
            cout<<"\n";
            return 0;
        }
    }

    stack<pair<int, int>>s;
    vector<vector<int>>g(n), g2(n);
    for(int i=0;i<n;i++){
        while(f[i]){
            auto& [x, y] = s.top();
            g[y].push_back(i);
            g2[y].push_back(i);
            g2[i].push_back(y);
            if(x <= f[i]){
                s.pop();
                f[i] -= x;
            }
            else{
                x -= f[i];
                f[i] = 0;
            }
        }
        if(h[i]) s.push({h[i], i});
        if(i) g[i-1].push_back(i);
    }

    {
        // 2 colors
        vector<int>c(n);
        bool two = true;
        vector<bool>vis(n);

        auto dfs = [&](auto& self, int u, int p)->void {
            vis[u] = 1;
            for(int v : g2[u]){
                if(v == p) continue;
                if(vis[v]){
                    if(c[v] == c[u]) two = false;
                    continue;
                } 
                c[v] = c[u] ^ 1;
                self(self, v, u);
            }
        };

        for(int i=0;i<n;i++) if(!vis[i]) dfs(dfs, i, i);

        if(two){
            cout<<"2\n";
            for(int i=0;i<n;i++) cout<<c[i] + 1<<" ";
            cout<<"\n";
            return 0;
        }
    }

    vector<int>c(n);
    queue<array<int, 3>>q;
    q.push({0, 1, 3});
    c[0] = 1;
    while(!q.empty()){
        auto [u, x, y] = q.front();
        q.pop();
        while(!g[u].empty() && c[g[u].back()]) g[u].pop_back();
        if(g[u].empty()) continue;
        int v = g[u].back();
        g[u].pop_back();
        int z = x ^ y;
        c[v] = z;
        q.push({u, x, z});
        q.push({v, z, y});
    }
    cout<<"3\n";
    for(int i=0;i<n;i++) cout<<c[i]<<" ";
    cout<<"\n";
    return 0;
}
