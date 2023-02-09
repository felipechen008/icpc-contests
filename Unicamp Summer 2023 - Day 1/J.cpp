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
    vector<int>d(n);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        d[a]++, d[b]++;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    queue<int>q;
    for(int i=0;i<n;i++){
        if(d[i] >= 2) q.push(i);
    }
    if(q.empty()){
        cout<<"1\n";
        for(int i=0;i<n;i++) cout<<i+1<<" ";
        cout<<"\n";
        return 0;
    }

    vector<int>c(n);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(d[u] < 2) continue;
        for(int v : g[u]){
            d[v] += (c[u] == c[v] ? -1 : 1);
            d[u] += (c[u] == c[v] ? -1 : 1);
            if(d[v] >= 2) q.push(v);
        }
        c[u] ^= 1;
    }
    cout<<"2\n";
    for(int i=0;i<n;i++) if(!c[i]) cout<<i+1<<" ";
    cout<<"\n";
    for(int i=0;i<n;i++) if(c[i]) cout<<i+1<<" ";
    cout<<"\n";

    return 0;
}
