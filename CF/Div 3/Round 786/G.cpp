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
    vector<int>d(n), in(n), out(n);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b);
        d[b]++;
        out[a]++;
        in[b]++;
    }
    vector<int>dp(n, 1);
    queue<int>q;
    for(int i=0;i<n;i++){
        if(!d[i]) q.push(i);
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : g[u]){
            d[v]--;
            if(!d[v]) q.push(v);
            if(in[v] > 1 && out[u] > 1) dp[v] = max(dp[v], dp[u] + 1);
        }
    }
    int ans = 0;
    for(int i=0;i<n;i++) ans = max(ans, dp[i]);
    cout<<ans<<"\n";


    return 0;
}
