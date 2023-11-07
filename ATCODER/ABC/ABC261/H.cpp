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
    int n, m, z;
    cin>>n>>m>>z; z--;
    vector<vector<pair<int, int>>>g(n);
    vector<vector<pair<int, int>>>h(n);
    vector<int>d(n);
    for(int i=0;i<m;i++){
        int a, b, c;
        cin>>a>>b>>c;
        a--, b--;
        g[a].emplace_back(b, c);
        h[b].emplace_back(a, c);
        d[a]++;
    }
    priority_queue<array<lint, 3>, vector<array<lint, 3>>, greater<array<lint, 3>>>pq;
    vector<vector<lint>>dist(n, {linf, -linf});
    for(int i=0;i<n;i++){
        if(!d[i]){
            dist[i][0] = dist[i][1] = 0;
            pq.push({0, 0, i});
            pq.push({0, 1, i});
        }
    }
    while(!pq.empty()){
        auto [w, t, u] = pq.top();
        pq.pop();
        if(dist[u][t] < w) continue;
        if(t == 0){
            for(auto [v, c] : h[u]){
                dist[v][1] = max(dist[v][1], dist[u][0] + c);
                d[v]--;
                if(!d[v]) pq.push({dist[v][1], 1, v});
            }
        }
        else{
            for(auto [v, c] : h[u]){
                if(dist[v][0] > dist[u][1] + c){
                    dist[v][0] = dist[u][1] + c;
                    pq.push({dist[v][0], 0, v});
                }
            }
        }
    }
    if(dist[z][0] == linf) cout<<"INFINITY\n";
    else cout<<dist[z][0]<<"\n";
    return 0;
}
