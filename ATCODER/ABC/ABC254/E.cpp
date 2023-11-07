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
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int>d(n, inf);
    int t;
    cin>>t;
    while(t--){
        int x, k;
        cin>>x>>k;
        x--;
        queue<int>q;
        d[x] = 0;
        vector<int>cur = {x}; 
        q.push(x);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            if(d[u] == k) continue;
            for(int v : g[u]){
                if(d[v] == inf){
                    d[v] = d[u] + 1;
                    q.push(v);
                    cur.push_back(v);
                }
            }
        }
        lint ans = 0;
        for(int i : cur) ans += i + 1, d[i] = inf;
        cout<<ans<<"\n";
    }

    return 0;
}
