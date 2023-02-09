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
    int n; lint a, b, s, t;
    cin>>n>>a>>b>>s>>t;
    vector<lint>p(n+4), h(n+4);
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) cin>>h[i];
    p[0] = a, h[0] = inf;
    p[n+1] = b, h[n+1] = inf;
    p[n+2] = s;
    p[n+3] = t;
    n += 4;
    vector<int>ids(n);
    iota(ids.begin(), ids.end(), 0);
    sort(ids.begin(), ids.end(), [&](int i, int j){
        return p[i] < p[j];
    });
    vector<int>in(n);
    for(int i=0;i<n;i++){
        int u = ids[i];
        in[u] = (p[u] == s || p[u] == t) ? u : u + n;
    }
    vector<vector<int>>g(2*n);
    for(int i=0;i<n;i++){
        int u = ids[i];
        lint mx = p[u], r = 0;
        for(int j=i+1;j<n;j++){
            int v = ids[j];
            if(mx < p[v] || (p[u] == s && p[v] == t && r == 0 && mx <= p[v]) ){
                g[u].emplace_back(in[v]);
                g[in[v]].emplace_back(u);
            }
            lint d = h[v] * h[v] / (p[v] - p[u]);
            lint nr = (h[v] * h[v] - d * (p[v] - p[u])) > 0;
            d += p[v];
            if(tie(mx, r) < tie(d, nr)){
                mx = d;
                r = nr;
            }
        }
    }
    
    int source = n-2, sink = n-1;

    vector<int>dist(2*n, inf);
    dist[source] = 0;
    queue<int>q;
    q.push(source);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : g[u]){
            if(dist[v] == inf){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    if(dist[sink] == inf) cout<<"-1\n";
    else cout<<dist[sink]<<"\n";

    return 0;
}
