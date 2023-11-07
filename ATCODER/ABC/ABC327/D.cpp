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
    int n, m;
    cin>>n>>m;
    vector<vector<int>>g(n);
    vector<int>a(m), b(m);
    for(int i=0;i<m;i++) cin>>a[i], a[i]--;
    for(int i=0;i<m;i++) cin>>b[i], b[i]--;
    for(int i=0;i<m;i++){
        g[a[i]].push_back(b[i]);
        g[b[i]].push_back(a[i]);
    }
    vector<int>c(n, -1);
    bool ok = true;
    auto dfs = [&](auto& self, int u)->void {
        for(int v : g[u]){
            if(c[v] == -1){
                c[v] = c[u] ^ 1;
                self(self, v);
            }
            else{
                if(c[v] != c[u] ^ 1) ok = false;
            }
        }
    };
    for(int i=0;i<n;i++) if(c[i] == -1){
        c[i] = 0;
        dfs(dfs, i);
    }
    if(ok) cout<<"Yes\n";
    else cout<<"No\n";
    
    return 0;
}
