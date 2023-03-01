#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<typename T = int> struct Dinitz {
	struct edge_t { int to, rev; T c, f; };
	vector<vector<edge_t>> adj;
	vector<int> lvl, ptr, q;
	Dinitz(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	inline void addEdge(int a, int b, T c, T rcap = 0) { // 694aae
		adj[a].push_back({b, (int)adj[b].size(), c, 0});
		adj[b].push_back({a, (int)adj[a].size() - 1, rcap, 0});
	}
	T dfs(int v, int t, T f) { // 8ffe6b
		if (v == t || !f) return f;
		for (int &i = ptr[v]; i < int(adj[v].size()); ++i) {
			edge_t &e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (T p = dfs(e.to, t, min(f, e.c - e.f))) {
					e.f += p, adj[e.to][e.rev].f -= p;
					return p;
				}
		}
		return 0;
	}
	T maxflow(int s, int t) { // db2141
		T flow = 0; q[0] = s;
		for (int L = 0; L < 31; ++L) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int>(q.size());
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (edge_t &e : adj[v])
					if (!lvl[e.to] && (e.c - e.f) >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (T p = dfs(s, t, numeric_limits<T>::max()/4)) flow += p;
		} while (lvl[t]);
		return flow;
	} 
	bool leftOfMinCut(int v) { return bool(lvl[v] != 0); }
	pair<T, vector<pair<int,int>>> minCut(int s, int t) { // 727b22
		T cost = maxflow(s,t); 
		vector<pair<int,int>> cut;		
		for (int i = 0; i < int(adj.size()); i++) for(edge_t &e : adj[i])
			if (lvl[i] && !lvl[e.to]) cut.push_back({i, e.to});
		return {cost, cut};
	} 
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>a(n), b(n);
        for(int i=0;i<n;i++) cin>>b[i];
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<n;i++) while( !(b[i]&1) ) b[i] >>= 1;
        vector<int>vals = b;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int m = int(size(vals));
        vector<int>f(m);
        for(int i=0;i<n;i++){
            int u = int(lower_bound(vals.begin(), vals.end(), b[i]) - vals.begin());
            f[u]++;
        }

        Dinitz<int>g(n+m+2);
        int source = n+m, sink = n+m+1;

        for(int i=0;i<n;i++){
            for(int j=0;j<30;j++){
                int c = a[i]>>j;
                if(!(c&1)) continue;
                int u = int(lower_bound(vals.begin(), vals.end(), c) - vals.begin());
                if(u == m || vals[u] != c) continue;
                g.addEdge(i, u+n, 1);
            }
            g.addEdge(source, i, 1);
        }
        for(int i=0;i<m;i++) g.addEdge(i+n, sink, f[i]);
        int ans = g.maxflow(source, sink);
        if(ans == n) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
