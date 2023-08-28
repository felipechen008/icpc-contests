#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

using G = vector<vector<int>>;
vector<int> val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));
	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = int(g.size());
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	for(int i = 0; i < n; ++i) if (comp[i] < 0) dfs(i, g, f);
}
pair<G, G> make_scc_dag(G &g){
	G vertOfComp;
	scc(g, [&](const vector<int> &vert){
		vertOfComp.push_back(vert);
	} );	
	G dag(ncomps);
	for(int u=0; u < int(g.size()); u++)
		for(int v:g[u])
			if(comp[u] != comp[v])
				dag[ comp[v] ].push_back(comp[u]);
	return { dag, vertOfComp };
}


int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin>>n>>m;
    G g(n);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b);
    }

    auto [rdag, _] = make_scc_dag(g);
    vector<int>f(ncomps), d(ncomps);
    for(int i=0;i<n;i++) f[comp[i]]++;
    vector<bool>w(ncomps);
    for(int i=0;i<ncomps;i++) w[i] = f[i] > 1;

    for(int u=0;u<n;u++){
        for(int v : g[u]){
            if(comp[v] != comp[u]) d[comp[u]]++;
        }
    }

    queue<int>q;
    for(int i=0;i<ncomps;i++){
        if(!d[i]) q.push(i);
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : rdag[u]){
            if(w[u]) w[v] = 1;
            d[v]--;
            if(!d[v]) q.push(v);
        }
    }
    int ans = 0;
    for(int i=0;i<n;i++) ans += w[comp[i]];
    cout<<ans<<"\n";

    return 0;
}
