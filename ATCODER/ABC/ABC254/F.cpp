#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<class T> struct segtree {
	int H, N;
	vector<T> ts;
	segtree() {}
	explicit segtree(int N_) {
		for (H = 0, N = 1; N < N_; ++H, N *= 2) {}
		ts.resize(2*N);
		build();
	}
	template<class Q> explicit segtree(const vector<Q>& qs) {
		const int N_ = int(qs.size());
		for (H = 0, N = 1; N < N_; ++H, N *= 2) {}
		ts.resize(2*N);
		for (int i = 0; i < N_; ++i) at(i) = T(qs[i]);
		build();
	}
	T& at(int a) { return ts[a + N]; }
	void build() { for (int a = N; --a; ) merge(a); }
	inline void merge(int a) { ts[a].merge(ts[2*a], ts[2*a+1]); }
	template<class S> void update(int a, const S& v) {
		assert(0 <= a && a < N);
		ts[a += N] = T(v);
		for (; a /= 2;) merge(a);
	}
	template<class F, class... Args> void update(int a, F f, Args &&... args) {
		assert(0 <= a && a < N);
		(ts[a += N].*f)(args...);
		for (; a /= 2;) merge(a);
	}
	T query(int a, int b) { 
		if (a == b) return T();
		a += N; b += N; 
		T lhs, rhs, t;
		for (int l = a, r = b; l < r; l /= 2, r /= 2) {
			if (l & 1) { t.merge(lhs, ts[l++]); lhs = t; }
			if (r & 1) { t.merge(ts[--r], rhs); rhs = t; }
		}
		t.merge(lhs, rhs); return t;
	}
	// da1cd
	template<class Op, class E, class F, class... Args> 
		auto query(int a, int b, Op op, E e, F f, Args&&... args) {
			if (a == b) return e();
			a += N; b += N;
			auto lhs = e(), rhs = e();
			for (int l = a, r = b; l < r; l /= 2, r /= 2) {
				if (l & 1) lhs = op(lhs, (ts[l++].*f)(args...));
				if (r & 1) rhs = op((ts[--r].*f)(args...), rhs);
			}
			return op(lhs, rhs);
		}
	// 1edda
	template<class F, class... Args> int find_right(int a, F f, Args &&... args) {
		assert(0 <= a && a <= N);
		if ((T().*f)(args...)) return a;
		if (a == N) return 1 + N;
		a += N;
		for (; ; a /= 2) if (a & 1) {
			if ((ts[a].*f)(args...)) {
				for (; a < N; ) {
					if (!(ts[a <<= 1].*f)(args...)) ++a;
				}
				return a - N + 1;
			}
			++a;
			if (!(a & (a - 1))) return N + 1;
		}
	} 
	// 76b20
	template<class F, class... Args> int find_left(int a, F f, Args &&... args) {
		assert(0 <= a && a <= N);
		if ((T().*f)(args...)) return a;
		if (a == 0) return -1;
		a += N;
		for (; ; a /= 2) if ((a & 1) || a == 2) {
			if ((ts[a - 1].*f)(args...)) {
				for (; a <= N; ) {
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
    int v;
    node(int n = 0): v(n) {}
    void merge(const node& l, const node& r){
        v = gcd(l.v, r.v);
    }
    int get(){ return v; }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin>>n>>q;
    segtree<node>sc(n-1), sr(n-1);
    vector<int>a(n), b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    for(int i=0;i<n-1;i++) sr.at(i) = node( abs(a[i+1] - a[i]) );
    for(int i=0;i<n-1;i++) sc.at(i) = node( abs(b[i+1] - b[i]) );
    sr.build();
    sc.build();
    while(q--){
        int l1, r1, l2, r2;
        cin>>l1>>l2>>r1>>r2;
        l1--, r1--, l2--, r2--;
        int g = a[l1] + b[r1], x = sr.query(l1, l2).get(), y = sc.query(r1, r2).get();
        int ans = gcd(g, gcd(x, y));
        cout<<ans<<"\n";

    }


    return 0;
}
