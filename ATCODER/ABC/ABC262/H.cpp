#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int minv(int a, int m) {
    a %= m; assert(a);
    return a == 1 ? 1 : int(m - int64_t(minv(m, a)) * m / a);
}
template<unsigned M_> struct modnum {
    static constexpr unsigned M = M_; using num = modnum;
    using ll = int64_t; using ull = uint64_t; unsigned x;
    num& norm(unsigned a){x = a<M ? a : a-M;return *this;}
    constexpr modnum(ll a = 0U) : x(unsigned((a %= ll(M)) < 0 ? a + ll(M) : a)) {}
    explicit operator int() const { return x; }
    num& operator+=(const num& a){ return norm(x+a.x); }
    num& operator-=(const num& a){ return norm(x-a.x+M); }
    num& operator*=(const num& a){ x = unsigned(ull(x)*a.x%M); return *this; }
    num& operator/=(const num& a){ return (*this *= a.inv());}
    num operator+(const num& a) const {return (num(*this) += a);}
    num operator-(const num& a) const {return (num(*this) -= a);}
    num operator*(const num& a) const {return (num(*this) *= a);}
    num operator/(const num& a) const {return (num(*this) /= a);}
    template<typename T> friend num operator+(T a, const num& b){ return (num(a) += b); }
    template<typename T> friend num operator-(T a, const num& b){ return (num(a) -= b); }
    template<typename T> friend num operator*(T a, const num& b){ return (num(a) *= b); }
    template<typename T> friend num operator/(T a, const num& b){ return (num(a) /= b); }
    num operator+() const { return *this; }
    num operator-() const { return num() - *this; }
    num pow(ll e) const {
        if (e < 0) { return inv().pow(-e); } num b = x, xe = 1U;
        for (; e; e >>= 1) { if (e & 1) xe *= b; b *= b; }
        return xe;
    }
    num inv() const { return minv(x, M); }
    friend num inv(const num& a) { return a.inv(); }
    explicit operator bool() const { return x; }
    friend bool operator==(const num& a, const num& b){return a.x == b.x;}
    friend bool operator!=(const num& a, const num& b){return a.x != b.x;}
};

template<class T> struct segtree_range {
    int H, N;
    vector<T> ts;
    segtree_range() {}
    explicit segtree_range(int N_) {
        for (H = 0, N = 1; N < N_; ++H, N *= 2) {}
        ts.resize(2*N);
        build();
    }
    template<class Q> explicit segtree_range(const vector<Q>& qs) {
        const int N_ = int(qs.size());
        for (H = 0, N = 1; N < N_; ++H, N *= 2) {}
        ts.resize(2*N);
        for (int i = 0; i < N_; ++i) at(i) = T(qs[i]);
        build();
    }
    T& at(int a) { return ts[a + N]; }
    void build() { for (int a = N; --a; ) merge(a); }
    inline void push(int a) { ts[a].push(ts[2 * a], ts[2 * a + 1]); }
    inline void merge(int a) { ts[a].merge(ts[2*a], ts[2*a+1]); }
    // f0fcbd
    void for_parents_down(int a, int b) {
        for (int h = H; h; --h) {
            const int l = (a >> h), r = (b >> h);
            if (l == r) {
                if ((l << h) != a || (r << h) != b) push(l);
            } else {
                if ((l << h) != a) push(l);
                if ((r << h) != b) push(r);
            }
        }
    }
    // a25cb
    void for_parents_up(int a, int b) {
        for (int h = 1; h <= H; ++h) {
            const int l = (a >> h), r = (b >> h);
            if (l == r) {
                if ((l << h) != a || (r << h) != b) merge(l);
            } else {
                if ((l << h) != a) merge(l);
                if ((r << h) != b) merge(r);
            }
        }
    }
    // 6014b
    template<class F, class... Args> void update(int a, int b, F f, Args&&... args) {
        if (a == b) return;
        a += N; b += N;
        for_parents_down(a, b);
        for (int l = a, r = b; l < r; l /= 2, r /= 2) {
            if (l & 1) (ts[l++].*f)(args...);
            if (r & 1) (ts[--r].*f)(args...);
        }
        for_parents_up(a, b);
    }
    T query(int a, int b) {
        if (a == b) return T();
        a += N; b += N;
        for_parents_down(a, b);
        T lhs, rhs, t;
        for (int l = a, r = b; l < r; l /= 2, r /= 2) {
            if (l & 1) { t.merge(lhs, ts[l++]); lhs = t; }
            if (r & 1) { t.merge(ts[--r], rhs); rhs = t; }
        }
        t.merge(lhs, rhs); return t;
    }
    // 5a862
    template<class Op, class E, class F, class... Args> 
        auto query(int a, int b, Op op, E e, F f, Args&&... args) {
            if (a == b) return e();
            a += N; b += N;
            for_parents_down(a, b);
            auto lhs = e(), rhs = e();
            for (int l = a, r = b; l < r; l /= 2, r /= 2) {
                if (l & 1) { lhs = op(lhs, (ts[l++].*f)(args...)); };
                if (r & 1) { rhs = op((ts[--r].*f)(args...), rhs); };
            }
            return op(lhs, rhs);
        }
    // aab16
    // find min i s.t. T::f(args...) returns true in [a, i) from left to right
    template<class F, class... Args> int find_right(int a, F f, Args &&... args) {
        assert(0 <= a && a <= N);
        if ((T().*f)(args...)) return a;
        if (a == N) return 1 + N;
        a += N;
        for (int h = H; h; --h) push(a >> h);
        for (; ; a /= 2) if (a & 1) {
            if ((ts[a].*f)(args...)) {
                for (; a < N; ) {
                    push(a);
                    if (!(ts[a <<= 1].*f)(args...)) ++a;
                }
                return a - N + 1;
            }
            ++a;
            if (!(a & (a - 1))) return N + 1;
        }
    } 
    // a033b
    // find max i s.t. T::f(args...) returns true in [i, a) from right to left
    template<class F, class... Args> int find_left(int a, F f, Args &&... args) {
        assert(0 <= a && a <= N);
        if ((T().*f)(args...)) return a;
        if (a == 0) return -1;
        a += N;
        for (int h = H; h; --h) push((a - 1) >> h);
        for (; ; a /= 2) if ((a & 1) || a == 2) {
            if ((ts[a - 1].*f)(args...)) {
                for (; a <= N; ) {
                    push(a - 1);
                    if (!(ts[(a <<= 1) - 1].*f)(args...)) --a;
                }
                return a - N - 1;
            }
            --a;
            if (!(a & (a - 1))) return -1;
        }
    }
};

struct node{
    int v, lz;
    node(int n = 0): v(n), lz(0) {}
    void push(node& l, node& r){
        if(lz){
            l.assign(lz);
            r.assign(lz);
            lz = 0;
        }
    } 
    void merge(const node& l, const node& r){
        v = max(l.v, r.v);
    }
    void assign(int n){
        v = lz = n;
    }
    int get(){ return v; }
};

using num = modnum<mod>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q;
    cin>>n>>m>>q;
    vector<array<int, 3>>que(q);
    vector<int>c;
    for(int i=0;i<q;i++){
        int l, r, x;
        cin>>l>>r>>x;
        l--, r--;
        c.push_back(x);
        que[i] = {l, r, x};
    }
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    int SZ = (int)c.size();
    vector<vector<pair<int, int>>>query(SZ);
    for(int i=0;i<q;i++){
        auto [l, r, x] = que[i];
        x = int(lower_bound(c.begin(), c.end(), x) - c.begin());
        query[x].emplace_back(l, r);        
    }
    vector<int>a(n, m + 1);
    segtree_range<node>seg(a);
    for(int i=SZ-1;i>=0;i--){
        for(auto [l, r] : query[i]){
            seg.update(l, r+1, &node::assign, c[i]);
        }
    }
    for(int i=SZ-1;i>=0;i--){
        for(auto [l, r] : query[i]){
            int u = seg.query(l, r+1).get();
            if(u < c[i]){
                cout<<"0\n";
                return 0;
            }
        }
    }
    for(int i=0;i<n;i++) a[i] = seg.query(i, i+1).get();
    vector<vector<int>>ind(SZ);
    for(int i=0;i<n;i++){
        if(a[i] == m + 1) continue;
        int x = int(lower_bound(c.begin(), c.end(), a[i]) - c.begin());
        ind[x].push_back(i);
    }
    for(int i=0;i<SZ;i++){
        auto& b = query[i];
        auto& v = ind[i];
        for(auto& [l, r] : b){
            l = int(lower_bound(v.begin(), v.end(), l) - v.begin());
            r = int(upper_bound(v.begin(), v.end(), r) - v.begin()) - 1;
        }
        int mn = n + 1;
        sort(b.begin(), b.end(), [&](pair<int, int>x, pair<int, int>y){
            if(x.st != y.st) return x.st > y.st;
            return x.nd < y.nd;
        });
        vector<pair<int, int>>cur;
        for(auto [l, r] : b){
            if(r < mn){
                mn = r;
                cur.emplace_back(l, r);
            }
        }
        swap(cur, b);
        reverse(b.begin(), b.end());
    }
    num ans = 1;
    for(int i=0;i<n;i++) if(a[i] == m + 1) ans *= m + 1; 
    for(int i=0;i<SZ;i++){
        auto& b = query[i];
        auto& v = ind[i];
        int sz = (int)v.size();
        vector<int>mx(sz + 1, -1);
        for(auto [l, r] : b) mx[r + 1] = l;
        for(int j=1;j<=sz;j++){
            if(mx[j] == -1) mx[j] = mx[j-1];
        }
        vector<num>pot(sz + 1), invs(sz + 1);
        pot[0] = invs[0] = 1;
        pot[1] = c[i], invs[1] = num(c[i]).inv();
        for(int j=2;j<=sz;j++) pot[j] = pot[j-1] * pot[1];
        for(int j=2;j<=sz;j++) invs[j] = invs[j-1] * invs[1];
        vector<num>dp(sz + 1), pref(sz + 1);
        dp[0] = pref[0] = 1;
        for(int j=0;j<sz;j++){
            dp[j+1] = pref[j] - (mx[j] == -1 ? 0 : pref[mx[j]]);
            dp[j+1] *= pot[j];
            pref[j+1] = pref[j] + dp[j+1] * invs[j+1];
        }
        auto [l, r] = b.back();
        num cur = ( pref[sz] - pref[l] ) * pot[sz];
        ans *= cur;
    }
    cout<<ans.x<<"\n";
    return 0;
}
