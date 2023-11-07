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
    vector<int>g(n), c(n), d(n);
    for(int i=0;i<n;i++) cin>>g[i], g[i]--, d[g[i]]++;
    for(int i=0;i<n;i++) cin>>c[i];
    queue<int>q;
    for(int i=0;i<n;i++) if(!d[i]) q.push(i);
    vector<bool>vis(n);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = 1;
        int v = g[u];
        d[v]--;
        if(!d[v]) q.push(v);
    }
    lint ans = 0;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            int mn = inf;
            int aux = i;
            while(!vis[aux]){
                vis[aux] = 1;
                mn = min(mn, c[aux]);
                aux = g[aux];
            }
            ans += mn;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
