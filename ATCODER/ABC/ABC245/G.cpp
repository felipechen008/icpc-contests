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
    int n, m, k, l;
    cin>>n>>m>>k>>l;
    vector<int>a(n), b(l);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<l;i++) cin>>b[i], b[i]--;
    vector<vector<pair<int, int>>>g(n);
    for(int i=0;i<m;i++){
        int u, v, w;
        cin>>u>>v>>w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector dist(n, vector<array<lint, 2>>(2, {linf, linf}));
    priority_queue<array<lint, 3>, vector<array<lint, 3>>, greater<array<lint, 3>>>pq;
    for(int i=0;i<l;i++){
        dist[b[i]][0] = {0, a[b[i]]};
        pq.push({0, b[i], a[b[i]]});
    }
    while(!pq.empty()){
        auto [w, u, pop] = pq.top();
        pq.pop();
        if(dist[u][0] != array<lint, 2>({w, pop}) && dist[u][1] != array<lint, 2>({w, pop}) ) continue;
        for(auto [v, c] : g[u]){
            auto [w0, p0] = dist[v][0];
            auto [w1, p1] = dist[v][1];
            if(w + c < w0){
                if(pop != p0) dist[v][1] = dist[v][0];
                dist[v][0] = {w + c, pop};
                pq.push({w+c, v, pop});
            }
            else if(pop != p0 && w + c < w1){
                dist[v][1] = {w + c, pop};
                pq.push({w+c, v, pop});
            }
        }
    }
    for(int i=0;i<n;i++){
        if(dist[i][0][0] == linf){
            cout<<"-1 ";
        }
        else if(dist[i][0][1] == a[i]){
            if(dist[i][1][0] == linf) cout<<"-1 ";
            else cout<<dist[i][1][0]<<" ";
        }
        else cout<<dist[i][0][0]<<" ";
    }
    cout<<"\n";

    
    return 0;
}
