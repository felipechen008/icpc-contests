#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct node{
    vector<pair<int, int>>v;
    node(int n = 0) : v(1){
        if(n <= 1) v[0] = {0, n};
        else v.emplace_back(n, n);
    }
};

node merge(const node& l, const node& r){
    int n = size(l.v), m = size(r.v);
    node cur;
    auto& v = cur.v;
    for(int i=0,lo=0,hi=0;i<n+m;i++){
        int x, y;
        if(lo == n) tie(x, y) = r.v[hi++];
        else if(hi == m) tie(x, y) = l.v[lo++];
        else if(l.v[lo].st <= r.v[hi].st) tie(x, y) = l.v[lo++];
        else tie(x, y) = r.v[hi++];
        auto& [a, b] = v.back();
        int c = a + b + (!a);
        if(x <= c) b += y;
        else v.emplace_back(x, y); 
    }
    return cur;
}

struct segtree{
    int n;
    vector<int>a;
    vector<node>tree;
    segtree(vector<int>_a, int _n): n(_n), a(_a), tree(4*_n){
        build(0, 0, n-1);
    }
    void build(int v, int l, int r){
        if(l == r){
            tree[v] = node(a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(2*v+1, l, m);
        build(2*v+2, m+1, r);
        tree[v] = merge(tree[2*v+1], tree[2*v+2]);
    }
    node query(int v, int a, int b, int l, int r){
        if(r < a || l > b) return node();
        if(a <= l && r <= b) return tree[v];
        int m = (l + r) >> 1;
        return merge( query(2*v+1, a, b, l, m),
                    query(2*v+2, a, b, m+1, r));
    }

};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    segtree seg(a, n);
    int q;
    cin>>q;
    while(q--){
        int l, r;
        cin>>l>>r;
        l--, r--;
        node ans = seg.query(0, l, r, 0, n-1);
        cout<<ans.v[0].nd + 1<<"\n";
    }


    return 0;
}
