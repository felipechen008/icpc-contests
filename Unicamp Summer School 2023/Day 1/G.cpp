#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

using G = vector<vector<int>>;
vector<int>val, comp, z, cont;
int Time, ncomps;
template<class G, class F>int dfs(int j, G& g, F& f){
  int low = val[j] = ++Time, x; z.push_back(j);
  for(auto e : g[j]) if(comp[e] < 0)
    low = min(low, val[e] ? : dfs(e, g, f));
    
  if(low == val[j]){
    do{
      x = z.back(); z.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    }  while(x != j);
    f(cont); cont.clear();
    ncomps++;
  }
  return val[j] = low;
}

template<class G, class F>void scc(G& g, F f){
  int n = int(size(g));
  val.assign(n, 0); comp.assign(n, -1);
  Time = ncomps = 0;
  for(int i=0;i<n;i++) if(comp[i] < 0) dfs(i, g, f);
}

pair<G, G> make_scc_dag(G &g){
  G vertOfComp;
  scc(g, [&](const vector<int> &vert){
    vertOfComp.push_back(vert);
  });
  G dag(ncomps), rdag(ncomps);
  for(int u=0;u<int(size(g));u++)
    for(int v : g[u]){
      if(comp[u] != comp[v]){
        dag[comp[u]].push_back(comp[v]);
        rdag[comp[v]].push_back(comp[u]);
      }
    }

  return {dag, rdag};
}


int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin>>n;

  vector<vector<int>>g(1000);
  vector<int>id(n);

  for(int i=0;i<n;i++){
    int m;
    cin>>id[i]>>m;
    for(int j=0;j<m;j++){
      int v;
      cin>>v;
      g[id[i]].push_back(v);
    }
  }

  auto [dag, rdag] = make_scc_dag(g);
  vector<bool>vis(ncomps);
  vector<bool>vis2(ncomps);

  auto dfs = [&](auto& self, int u)->void {
    vis[u] = 1;
    for(int v : dag[u]){
      if(!vis[v]) self(self, v);
    }
  };
  auto dfs2 = [&](auto& self, int u)->void {
    vis2[u] = 1;
    for(int v : rdag[u]){
      if(!vis2[v]) self(self, v);
    }
  };

  dfs(dfs, comp[0]);
  dfs2(dfs2, comp[0]);

  int ans = 0;
  for(int i=0;i<n;i++){
    if(comp[id[i]] == comp[0]) continue;
    ans++;
    if(vis[comp[id[i]]]) cout<<"TRAPPED "<<id[i]<<"\n";
    else if(!vis2[comp[id[i]]]) cout<<"TRAPPED "<<id[i]<<"\n";
  }

  for(int i=0;i<n;i++){
    if(comp[id[i]] == comp[0]) continue;
    ans++;
    if(vis2[comp[id[i]]]) cout<<"UNREACHABLE "<<id[i]<<"\n";
    else if(!vis[comp[id[i]]]) cout<<"UNREACHABLE "<<id[i]<<"\n";
  }
  if(!ans) cout<<"NO PROBLEMS\n";

  return 0;
}