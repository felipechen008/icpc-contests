#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct node{
    lint sum, pref, suf, ans;
    node(lint x = -inf, lint y = 0): sum(x), pref(y), suf(y), ans(y){}
};
node merge(const node& l, const node& r){
    node cur;
    cur.sum = l.sum + r.sum;
    cur.pref = max(l.pref, l.sum + r.pref);
    cur.suf = max(r.suf, l.suf + r.sum);
    cur.ans = max({l.ans, r.ans, l.suf + r.pref});
    return cur;
}

struct segtree{
    vector<node>tree;
    segtree(int n): tree(20*n) {}
    void update(int v, int l, int r, int pos, int val){
        if(pos < l || pos > r) return;
        if(l == r){
            tree[v] = node(val, val);
            return;
        }
        int m = (l + r) >> 1;
        update(2*v+1, l, m, pos, val);
        update(2*v+2, m+1, r, pos, val);
        tree[v] = merge(tree[2*v+1], tree[2*v+2]);
    }
    node query(int v, int l, int r, int a, int b){
        if(b < l || a > r) return node();
        if(a <= l && r <= b) return tree[v];
        int m = (l + r) >> 1;
        return merge(query(2*v+1, l, m, a, b), 
                    query(2*v+2, m+1, r, a, b));
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int>h(n);
    for(int i=0;i<n;i++) cin>>h[i];
    vector<int>val = h;
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int m = int(size(val));
    for(int& u : h){
        u = int(lower_bound(val.begin(), val.end(), u) - val.begin());
        u = m - 1 - u;
    }
    vector<vector<int>>ind(m);
    for(int i=0;i<n;i++) ind[h[i]].push_back(i);

    int q;
    cin>>q;
    vector<array<int, 3>>qr(q);
    for(int i=0;i<q;i++){
        int l, r, w;
        cin>>l>>r>>w;
        l--, r--;
        qr[i] = {l, r, w};
    }
    vector<int>lo(q), hi(q, m-1);
    for(int z=0;z<18;z++){
        vector<vector<int>>ids(m);
        for(int i=0;i<q;i++){
            int mid = (lo[i] + hi[i]) / 2;
            ids[mid].push_back(i);
        }
        segtree seg(n);
        for(int i=0;i<m;i++){
            for(int j : ind[i]) seg.update(0, 0, n-1, j, 1);
            for(int j : ids[i]){
                auto [l, r, w] = qr[j];
                node cnt = seg.query(0, 0, n-1, l, r);
                if(cnt.ans >= w) hi[j] = i - 1;
                else lo[j] = i + 1; 
            }
        }
    }
    for(int i=0;i<q;i++){
        int j = m - 1 - lo[i];
        cout<<val[j]<<"\n";
    }


    return 0;
}
