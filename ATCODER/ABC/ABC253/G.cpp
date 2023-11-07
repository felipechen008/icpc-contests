#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct node {
    int v, p, sz;
    node *l, *r;
    bool rev;
    node(int k) : v(k), p(rng()), l(nullptr), rev(0), r(nullptr), sz(0) {}
};
int sz(node *t) {
    if (t == nullptr) return 0;
    return t->sz;
}
void push(node *t) {
    if (t == nullptr) return;
    if (t->rev) {
        swap(t->l, t->r);
        if (t->l != nullptr) t->l->rev ^= t->rev;
        if (t->r != nullptr) t->r->rev ^= t->rev;
        t->rev = 0;
    }
}
void updsz(node *t) {
    if (t == nullptr) return;
    push(t); push(t->l); push(t->r);
    t->sz = sz(t->l) + sz(t->r) + 1;
}
void split(node *t, node *&l, node *&r, int k) { //k on left
    push(t);
    if (t == nullptr) l = r = nullptr;
    else if (k <= sz(t->l)) {
        split(t->l, l, t->l, k);
        r = t;
    } 
    else {
        split(t->r, t->r, r, k-1-sz(t->l));
        l = t;
    }
    updsz(t);
}
void merge(node *&t, node *l, node *r) {
    push(l); push(r);
    if (l == nullptr) t = r;
    else if (r == nullptr) t = l;
    else if (l->p <= r->p) {
        merge(l->r, l->r, r);
        t = l;
    }
    else {
        merge(r->l, l, r->l);
        t = r;
    }
    updsz(t);
}
void add(node *&t, node *c, int k) {
    push(t);
    if (t == nullptr) t = c;
    else if (c->p >= t->p) {
        split(t, c->l, c->r, k);
        t = c;
    }
    else if (sz(t->l) >= k) add(t->l, c, k);
    else add(t->r, c, k-1-sz(t->l));
    updsz(t);
}
void del(node *&t, int k) {
    push(t);
    if (t == nullptr) return;
    if (sz(t->l) == k) merge(t, t->l, t->r);
    else if (sz(t->l) > k) del(t->l, k);
    else del(t->r, k);
    updsz(t);
}
void print(node *t) {
    if (t == nullptr) return;
    print(t->l);
    cout << t->v << ' ';
    print(t->r); 
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    node *treap = nullptr;
    lint n, l, r;
    cin>>n>>l>>r;
    for(int i=0;i<n;i++){
        node *c = new node(i + 1);
        add(treap, c, i);
    }

    vector<array<int, 3>>vals;
    for(lint i=0;i<n;i++){
        if(l > n - 1 - i) l -= n - 1 - i, r -= n - 1 - i;
        else{
            for(lint k=i;k<n;k++){
                lint be = max(k + 1, k + l), en = min(n - 1, k + r);
                vals.push_back({k, be, en});
                l -= n - 1 - k;
                r -= n - 1 - k;
                if(r <= 0) break;
            }
            break;
        }
    }
    for(auto [i, be, en] : vals){
        node *x1, *x2, *x3, *x4, *x5, *x6;
        split(treap, x5, x6, en + 1);
        split(x5, x4, x5, en);
        split(x4, x3, x4, be);
        split(x3, x2, x3, i+1);
        split(x2, x1, x2, i);
        merge(treap, x1, x5);
        merge(treap, treap, x3);
        merge(treap, treap, x2);
        merge(treap, treap, x4);
        merge(treap, treap, x6);
    }
    print(treap);
    cout<<"\n";

    return 0;
}
