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
    int k;
    cin>>k;
    vector<vector<int>>poss(k);
    vector<bool>can(n), cannot(n);
    for(int i=0;i<k;i++){
        int r, di;
        cin>>r>>di;
        r--;
        vector<int>d(n, inf);
        d[r] = 0;
        queue<int>q;
        q.push(r);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            if(d[u] < di) cannot[u] = 1;
            else if(d[u] == di) poss[i].push_back(u);
            for(int v : g[u]){
                if(d[v] == inf){
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    vector<bool>black(n);
    for(int i=0;i<n;i++){
        if(!cannot[i]) black[i] = 1;
    }

    int cur = 0;
    for(int i=0;i<k;i++){
        int cnt = 0;
        for(int j : poss[i]) cnt += black[j];
        if(!cnt) cur++;
    }
    if(cur) cout<<"No\n";
    else{
        cout<<"Yes\n";
        for(int i=0;i<n;i++) cout<<black[i];
        cout<<"\n";
    }


    return 0;
}
