#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct segtree{
    struct node{
        int v, l, r;
        node(int _v = 0, int _l = 0, int _r = 0): v(_v), l(_l), r(_r) {}
    };
    int id;
    vector<node>tree;
    segtree(int n): id(1), tree(20*n){}
    int update(int v, int l, int r, int pos, int y){
        if(pos < l || pos > r) return v;
        if(l == r){
            tree[id] = node(tree[v].v + y);
            return id++;
        }
        int m = (l + r) >> 1;
        int lo = update(tree[v].l, l, m, pos, y);
        int hi = update(tree[v].r, m+1, r, pos, y);
        tree[id] = node(tree[lo].v + tree[hi].v, lo, hi);
        return id++;
    }
    int query(int a, int b, int c, int d, int l, int r, int k){
        if(l == r) return l;
        int m = (l + r) >> 1;
        int cnt = tree[tree[a].l].v + tree[tree[b].l].v
                - tree[tree[c].l].v - tree[tree[d].l].v;

        if(k <= cnt) return query(tree[a].l, tree[b].l, tree[c].l, tree[d].l, l, m, k);
        return query(tree[a].r, tree[b].r, tree[c].r, tree[d].r, m+1, r, k - cnt);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin>>n>>q;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int>val = a;
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for(int& u : a){
        u = int(lower_bound(val.begin(), val.end(), u) - val.begin());
    }
    vector<vector<int>>g(n), anc(18, vector<int>(n));
    for(int i=1;i<n;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int timer = 0;
    vector<int>tin(n), tout(n), h(n), ver(2*n);
    auto dfs = [&](auto& self, int u, int p)->void {
        ver[timer] = u; 
        tin[u] = timer++;
        anc[0][u] = p;
        for(int v : g[u]){
            if(v == p) continue;
            h[v] = h[u] + 1;
            self(self, v, u);
        }
        ver[timer] = u + n; 
        tout[u] = timer++;
    };

    dfs(dfs, 0, 0);

    for(int b=1;b<18;b++){
        for(int i=0;i<n;i++) anc[b][i] = anc[b-1][anc[b-1][i]];
    }

    auto get_lca = [&](int u, int v)->int {
        if(h[u] < h[v]) swap(u, v);
        int d = h[u] - h[v];
        for(int b=17;b>=0;b--) if(d>>b&1) u = anc[b][u];
        for(int b=17;b>=0;b--) if(anc[b][u] != anc[b][v]) u = anc[b][u], v = anc[b][v];
        if(u != v) u = anc[0][u];
        return u;
    };

    segtree seg(2*n);
    vector<int>roots(2*n+1);
    for(int i=0;i<n+n;i++){
        if(ver[i] < n) roots[i+1] = seg.update(roots[i], 0, n-1, a[ver[i]], 1);
        else roots[i+1] = seg.update(roots[i], 0, n-1, a[ver[i]-n], -1);
    }

    for(int i=0;i<q;i++){
        int u, v, k;
        cin>>u>>v>>k;
        u--, v--;
        int lca = get_lca(u, v);
        int c = seg.query(roots[tin[u]+1], roots[tin[v]+1], roots[tin[lca]+1], roots[tin[lca]], 0, n-1, k);
        cout<<val[c]<<"\n";
    }
    return 0;
}
