#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int lim = 2e7 + 10;

template<typename T = int> struct Dinitz {
    struct edge_t { int to, rev; T c, f; };
    vector<vector<edge_t>> adj;
    vector<int> lvl, ptr, q;
    Dinitz(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    inline void addEdge(int a, int b, T c, T rcap = 0) {
        adj[a].push_back({b, (int)adj[b].size(), c, 0});
        adj[b].push_back({a, (int)adj[a].size() - 1, rcap, 0});
    }
    T dfs(int v, int t, T f) {///start-hash
        if (v == t || !f) return f;
        for (int &i = ptr[v]; i < int(adj[v].size()); ++i) {
            edge_t &e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (T p = dfs(e.to, t, min(f, e.c - e.f))) {
                    e.f += p, adj[e.to][e.rev].f -= p;
                    return p;
                }
        } return 0;
    }///end-hash
    T maxflow(int s, int t) {///start-hash
        T flow = 0; q[0] = s;
        for (int L = 0; L < 31; ++L) do { // consider L = 30
            lvl = ptr = vector<int>(q.size());
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (edge_t &e : adj[v])
                    if (!lvl[e.to] && (e.c - e.f) >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while(T p =dfs(s, t, numeric_limits<T>::max()/4))flow+=p;
        } while (lvl[t]);
        return flow;
    }///end-hash 
    bool leftOfMinCut(int v) { return bool(lvl[v] != 0); }
    auto minCut(int s, int t) {///start-hash
        T cost = maxflow(s,t); 
        vector<edge_t> cut;		
        for (int i = 0; i < int(adj.size()); i++) for(edge_t &e : adj[i])
            if (lvl[i] && !lvl[e.to]) cut.push_back(e);
        return make_pair(cost, cut);
    }///end-hash
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<int>lp(lim+1), primes;
    primes.reserve(lim+1);
    for(int i=2;i<=lim;i++){
        if(!lp[i]) lp[i] = i, primes.push_back(i);
        for(int p : primes){
            if(p > lim/i) break;
            lp[p * i] = p;
            if(i % p == 0) break;
        }
    }

    int n;
    cin>>n;
    vector<int>a(n), b(n);
    for(int i=0;i<n;i++) cin>>a[i]>>b[i];
    int s = 2*n, t = 2*n+1;
    Dinitz<lint>g(2*n + 2);
    for(int i=0;i<n;i++) g.addEdge(s, i, b[i]);
    for(int i=0;i<n;i++) g.addEdge(i+n, t, b[i]);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(lp[a[i] + a[j]] == a[i] + a[j]){
                g.addEdge(i, j+n, min(b[i], b[j]));
            }
        }
    }
    lint ans = g.maxflow(s, t);
    cout<<ans/2<<"\n";
    return 0;
}
