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
    int n, k;
    cin>>n>>k;
    n++;
    vector<int>p(n), c(n), d(n);
    vector<vector<int>>g(n);
    for(int i=1;i<n;i++){
        cin>>p[i]>>c[i]>>d[i];
        g[p[i]].push_back(i);
    }

    int ans = k;
    vector<int>sum(n), need(n);
    for(int i=0;i<n;i++) sum[i] = d[i], need[i] = c[i] - d[i];
    need[0] = k;

    auto dfs = [&](auto& self, int u)->void {
        ans = min(ans, need[u]);
        for(int v : g[u]){
            need[v] = max(need[v], need[u] - d[v]);
            sum[v] += sum[u];
            self(self, v);
        }
    };
    dfs(dfs, 0);
    cout<<ans<<"\n";

    return 0;
}
