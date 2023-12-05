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
    vector<lint>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<vector<int>>g(n);
    for(int i=0;i<m;i++){
        int x, y;
        cin>>x>>y;
        x--, y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    lint lo = 0, hi = 1e15;
    while(lo <= hi){
        lint mid = (lo + hi) >> 1;
        vector<lint>c(n);
        for(int i=0;i<n;i++){
            for(int j : g[i]) c[i] += a[j];
        }
        queue<int>q;
        vector<bool>w(n);
        for(int i=0;i<n;i++){
            if(c[i] <= mid) w[i] = 1, q.push(i);
        }
        int t = 0;
        while(!q.empty()){
            t++;
            int u = q.front();
            q.pop();
            for(int v : g[u]){
                c[v] -= a[u];
                if(c[v] <= mid && !w[v]) w[v] = 1, q.push(v);
            }
        }
        if(t == n) hi = mid - 1;
        else lo = mid + 1;
    }
    cout<<lo<<"\n";
    return 0;
}
