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
    vector<vector<bool>>g(n, vector<bool>(n));
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a][b] = 1;
        g[b][a] = 1;
    }
    vector<vector<int>>d(1<<n, vector<int>(n, inf));
    queue<pair<int, int>>q;
    for(int i=0;i<n;i++) d[0][i] = 0;
    for(int i=0;i<n;i++) d[1<<i][i] = 1, q.push({1<<i, i});
    while(!q.empty()){
        auto [mask, u] = q.front();
        q.pop();
        for(int v=0;v<n;v++){
            if(g[u][v]){
                int nmask = mask ^ (1<<v);
                if(d[nmask][v] == inf){
                    d[nmask][v] = d[mask][u] + 1;
                    q.push({nmask, v});
                }
            }
        }
    }
    int ans = 0;
    for(int mask=0;mask<1<<n;mask++){
        int cur = inf;
        for(int i=0;i<n;i++) cur = min(cur, d[mask][i]);
        ans += cur;
    }
    cout<<ans<<"\n";

    return 0;
}
