#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

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

using G = vector<vector<pair<int,int>>>; 

template<typename T, bool USE_EDGES> struct heavylight_t { // b60237
	int t, n;
	vector<int> chain, par;
	vector<int> timer, preorder;
	vector<int> dep, sz;
	vector<T> val;
	heavylight_t() {}
	heavylight_t(G &g, int r = 0) : t(0), n(g.size()), chain(n, -1), par(n, -1),
	timer(n), preorder(n), dep(n), sz(n), val(n) { par[r] = chain[r] = r;
		dfs_sz(g, r), dfs_hld(g, r);
	}
	int dfs_sz(G &g, int u) {
		int subtree = 1;
		for(auto &e : g[u]) {
			int v = e.first;
			if (par[v] != -1) continue;
			par[v] = u; dep[v] = dep[u] + 1;
			subtree += dfs_sz(g, v);
			if (sz[v] > sz[g[u][0].first]) swap(g[u][0], e);
		}
		return sz[u] = subtree;
	}
	void dfs_hld(G &g, int u) {
		preorder[timer[u] = t++] = u;
		for (auto &e : g[u]) {
			int v = e.first;
			if (chain[v] != -1) continue;
			chain[v] = (e == g[u][0] ? chain[u] : v);
			dfs_hld(g, v);
			if (USE_EDGES) val[timer[v]] = e.second;
		}
	}
	template<class F> void path(int u, int v, F op) {
		if (u == v) return op(timer[u], timer[u], 0);
		int cnt = 0;
		for(int e, p; chain[u] != chain[v]; u = p) {
			if (dep[chain[u]] < dep[chain[v]]) swap(u,v), cnt++;
			u == (p = chain[u]) ? e = 0, p = par[u] : e = 1;
			op(timer[chain[u]] + e, timer[u], cnt&1);
		}
		if (timer[u] > timer[v]) swap(u, v), cnt++;
		op(timer[u] + USE_EDGES, timer[v], (++cnt)&1);
	}
};

template<typename T>struct seg_node{
    vector<T> sum;
    int sz, lz;
    seg_node(int v = 0): sum(7), sz(1), lz(-1){}
    void push(seg_node& l, seg_node& r){
        if(lz != -1){
            l.add(lz);
            r.add(lz);
            lz = -1;
        }
    }
    void merge(const seg_node& l, const seg_node& r){
        for(int i=0;i<7;i++) sum[i] = l.sum[i] + r.sum[i];
        sz = l.sz + r.sz;
    }
    void add(T v){
        for(int i=0;i<7;i++){
            if(i == v) sum[i] = sz;
            else sum[i] = 0;
        }
        lz = v;
    }
    T get_sum(T c){ return sum[c]; }
};

template<typename T, bool USE_EDGES> struct hld_solver { // a21ccc
	heavylight_t<T, USE_EDGES> h;
    segtree_range<seg_node<T> > seg;
	
	hld_solver(const heavylight_t<T, USE_EDGES> &g) : h(g) {
		seg = segtree_range<seg_node<T> >(h.val);
	}

	T queryPath(int u, int v, int k) {
        int cnt = 0;
		h.path(u, v, [&](int a,int b, int cur) {
            cnt += b - a + 1;
            cnt -= seg.query(a, b+1).get_sum(k);
            seg.update(a, b+1, &seg_node<T>::add, k);
		});
		return cnt;
	}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    G g(n);
    for(int i=1;i<n;i++){
        int a, b;
        cin>>a>>b;
        g[a].emplace_back(b, 0);
        g[b].emplace_back(a, 0);
    }

    heavylight_t<int, true>h(g);
    hld_solver<int, true>seg(h);

    int q;
    cin>>q;
    vector<string>s = {"red", "orange", "yellow", "green", "blue", "indigo", "violet"};
    map<string, int>id;
    for(int i=0;i<7;i++) id[s[i]] = i;

    vector<lint>ans(7);
    while(q--){
        int a, b, c;
        string t;
        cin>>a>>b>>t;
        c = id[t];
        int cnt = seg.queryPath(a, b, c);
        ans[c] += cnt;
    }
    for(int i=0;i<7;i++) cout<<s[i]<<" "<<ans[i]<<"\n";

    return 0;
}
