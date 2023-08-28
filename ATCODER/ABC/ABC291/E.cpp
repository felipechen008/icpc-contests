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
        int x, y;
        cin>>x>>y;
        x--, y--;
        g[x].push_back(y);
        d[y]++;    
    }
    queue<int>q;
    for(int i=0;i<n;i++){
        if(!d[i]) q.push(i);
    }

    vector<int>ans(n), ids;
    while(!q.empty()){
        if(int(size(q)) > 1){
           cout<<"No\n";
            return 0;
        }
        int u = q.front();
        q.pop();
        ids.push_back(u);
        for(int v : g[u]){
            d[v]--;
            if(!d[v]) q.push(v);
        }
    }
    if(int(size(ids)) != n){
        cout<<"No\n";
        return 0;
    }
    for(int i=0;i<n;i++){
        ans[ids[i]] = i;
    }
    cout<<"Yes\n";
    for(int i : ans) cout<<i+1<<" ";
    cout<<"\n";
    return 0;
}
