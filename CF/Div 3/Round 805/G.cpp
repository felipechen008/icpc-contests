#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct FT{
    vector<int>s;
    FT(int n) : s(n) {}
    void update(int pos, int dif){
        for(;pos<int(size(s));pos |= pos + 1) s[pos] += dif;
    }
    int query(int pos){
        int res = 0;
        for(;pos;pos &= pos - 1) res += s[pos - 1];
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    for(int i=1;i<n;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int timer = 0;
    vector<int>tin(n), tout(n), h(n);
    vector<vector<int>>anc(19, vector<int>(n));
    auto dfs = [&](auto& self, int u, int p)->void {
        tin[u] = timer++;
        anc[0][u] = p;
        for(int v : g[u]){
            if(v == p) continue;
            h[v] = h[u] + 1;
            self(self, v, u);

        }
        tout[u] = timer++;
    };

    dfs(dfs, 0, 0);

    for(int b=1;b<19;b++){
        for(int i=0;i<n;i++) anc[b][i] = anc[b-1][anc[b-1][i]];
    }

    auto get_lca = [&](int u, int v)->int {
        if(h[u] < h[v]) swap(u, v);
        int d = h[u] - h[v];
        for(int b=18;b>=0;b--) if(d>>b&1) u = anc[b][u];
        for(int b=18;b>=0;b--) if(anc[b][u] != anc[b][v]) u = anc[b][u], v = anc[b][v];
        if(u != v) u = anc[0][u];
        return u;
    };

    FT seg(n + n);

    int q;
    cin>>q;
    while(q--){
        int m;
        cin>>m;
        vector<int>a(m);
        for(int i=0;i<m;i++) cin>>a[i], a[i]--;
        for(int i=0;i<m;i++) seg.update(tin[a[i]], 1), seg.update(tout[a[i]], -1);
        int x = a[0], y = a[0];
        for(int i=0;i<m;i++){
            if(tin[a[i]] > tin[y]) y = a[i];
            if(tout[a[i]] < tout[x]) x = a[i];
        }
        int lca = get_lca(x, y);
        int ans = seg.query(tin[x] + 1) + seg.query(tin[y] + 1) - seg.query(tin[lca] + 1) - seg.query(tin[lca]);
        if(ans == m || x == y) cout<<"YES\n";
        else cout<<"NO\n";

        for(int i=0;i<m;i++) seg.update(tin[a[i]], -1), seg.update(tout[a[i]], 1);
    }

    return 0;
}
