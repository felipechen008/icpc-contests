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
    string s;
    cin>>s;
    vector<bool>vis(n);
    vector<int>cnt(n);
    vector<int>ans;
    auto dfs = [&](auto& self, int u)->void {
        cnt[u] ^= 1;
        vis[u] = 1;
        ans.push_back(u);
        for(int v : g[u]){
            if(!vis[v]){
                self(self, v);
                cnt[u] ^= 1;
                ans.push_back(u);
                if(s[v] - '0' != cnt[v]){
                    cnt[v] ^= 1;
                    cnt[u] ^= 1;
                    ans.push_back(v);
                    ans.push_back(u);
                }
            }
        }
    };
    for(int i=0;i<n;i++) sort(g[i].begin(), g[i].end());

    dfs(dfs, 0);
    if(s[0] - '0' != cnt[0]){
        ans.pop_back();
        cnt[0] ^= 1;
    }
    cout<<size(ans)<<"\n";
    for(int u : ans) cout<<u + 1<<" ";
    cout<<"\n";
    return 0;
}
