#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<class flow_t, class cost_t> struct min_cost {
  // Watch out when using types other than int and long long.
  static constexpr flow_t FLOW_EPS = 1e-10L;
  static constexpr flow_t FLOW_INF = std::numeric_limits<flow_t>::max();
  static constexpr cost_t COST_EPS = 1e-10L;
  static constexpr cost_t COST_INF = std::numeric_limits<cost_t>::max();

  int n, m;
  vector<int> ptr, nxt, zu;
  vector<flow_t> capa;
  vector<cost_t> cost;

  explicit min_cost(int n_) : n(n_), m(0), ptr(n_, -1) {}
  int add_edge(int u, int v, flow_t w, cost_t c) { // d482f5
    assert(0 <= u); assert(u < n);
    assert(0 <= v); assert(v < n);
    assert(0 <= w);
    nxt.push_back(ptr[u]); zu.push_back(v); capa.push_back(w); cost.push_back( c); ptr[u] = m++;
    nxt.push_back(ptr[v]); zu.push_back(u); capa.push_back(0); cost.push_back(-c); ptr[v] = m++;
    return m - 2;
  }

  vector<cost_t> pot, dist;
  vector<bool> vis;
  vector<int> pari;

  // cost slopes[j] per flow when flows[j] <= flow <= flows[j + 1]
  vector<flow_t> flows;
  vector<cost_t> slopes;

  // Finds a shortest path from s to t in the residual graph.
  // O((n + m) log m) time.
  //   Assumes that the members above are set.
  //   The distance to a vertex might not be determined if it is >= dist[t].
  //   You can pass t = -1 to find a shortest path to each vertex.
  void shortest(int s, int t) { // e9bb0d
    using Entry = pair<cost_t, int>;
    priority_queue<Entry, vector<Entry>, std::greater<Entry>> que;
    for (int u = 0; u < n; ++u) { dist[u] = COST_INF; vis[u] = false; }
    for (que.emplace(dist[s] = 0, s); !que.empty(); ) {
      const cost_t c = que.top().first;
      const int u = que.top().second;
      que.pop();
      if (vis[u]) continue;
      vis[u] = true;
      if (u == t) return;
      for (int i = ptr[u]; ~i; i = nxt[i]) if (capa[i] > FLOW_EPS) {
        const int v = zu[i];
        const cost_t cc = c + cost[i] + pot[u] - pot[v];
        if (dist[v] > cc) { que.emplace(dist[v] = cc, v); pari[v] = i; }
      }
    }
  }

  // Finds a minimum cost flow from s to t of amount min{(max flow), limFlow}.
  //   Bellman-Ford takes O(n m) time, or O(m) time if there is no negative-cost
  //   edge, or cannot stop if there exists a negative-cost cycle.
  //   min{(max flow), limFlow} shortest paths if Flow is an integral type.
  // d9868f
  pair<flow_t, cost_t> run(int s, int t, flow_t limFlow = FLOW_INF) {
    assert(0 <= s); assert(s < n);
    assert(0 <= t); assert(t < n);
    assert(s != t);
    assert(0 <= limFlow);
    pot.assign(n, 0);
    for (; ; ) {
      bool upd = false;
      for (int i = 0; i < m; ++i) if (capa[i] > FLOW_EPS) {
        const int u = zu[i ^ 1], v = zu[i];
        const cost_t cc = pot[u] + cost[i];
        if (pot[v] > cc + COST_EPS) { pot[v] = cc; upd = true; }
      }
      if (!upd) break;
    }
    dist.resize(n);
    vis.resize(n);
    pari.resize(n);
    flows.clear(); flows.push_back(0);
    slopes.clear();
    flow_t flow = 0;
    cost_t cost = 0;
    for (; flow < limFlow; ) {
      shortest(s, t);
      if (!vis[t]) break;
      for (int u = 0; u < n; ++u) pot[u] += min(dist[u], dist[t]);
      flow_t f = limFlow - flow;
      for (int v = t; v != s; ) {
        const int i = pari[v]; if (f > capa[i]) { f = capa[i]; } v = zu[i ^ 1];
      }
      for (int v = t; v != s; ) {
        const int i = pari[v]; capa[i] -= f; capa[i ^ 1] += f; v = zu[i ^ 1];
      }
      flow += f;
      cost += f * (pot[t] - pot[s]);
      flows.push_back(flow); slopes.push_back(pot[t] - pot[s]);
    }
    return make_pair(flow, cost);
  }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin>>n>>m;
    vector<vector<string>>s(n, vector<string>(m));
    vector<vector<int>>ones(n, vector<int>(m));
    vector<vector<int>>cp(n, vector<int>(m));

    int two = 0, ans = 0, flow = 0;    
    int tot = n * m;
    int source = tot, sink = tot+1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>s[i][j];
            for(int k=0;k<4;k++) if(s[i][j][k] == '1') ones[i][j]++;
            ans -= 2 * (ones[i][j] == 3);
            flow += ones[i][j];
            if(ones[i][j] == 2) cp[i][j] = tot+2+two++;
        }
    }

    min_cost<int, int>g(tot+2+two);
    vector<pair<int, int>>dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    auto get_cost = [&](int i, int j, int l)->int {
        if(ones[i][j] == 1){
            int id = -1;
            for(int k=0;k<4;k++) if(s[i][j][k] == '1') id = k;
            return min( (id+4 - l)%4, (4+l - id)%4 );
        }
        if(ones[i][j] == 3){
            int id = -1;
            for(int k=0;k<4;k++){
                if(s[i][j][k] == '1' && s[i][j][(k+1)%4] == '1'
                    && s[i][j][(k+3)%4] == '1') id = k;
            }
            return min( (id+4 - l)%4, (4+l - id)%4 );
        }
        if(ones[i][j] == 4) return 0;
        return s[i][j][l] != '1';
    };

    auto add = [&](int cur, int ni, int nj, int k, int cost)->void {
        int nxt = ni*m + nj;
        cost += get_cost(ni, nj, k);
        if(ones[ni][nj] != 2){
            g.add_edge(cur, nxt, 1, cost);
            return;
        }
        int copy = cp[ni][nj];
        if(k&1) g.add_edge(cur, copy, 1, cost);
        else g.add_edge(cur, nxt, 1, cost);
    };

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!ones[i][j]) continue;
            int cur = i*m + j;
            if((i+j)&1){
                if(ones[i][j] == 2){
                    int copy = cp[i][j];
                    g.add_edge(cur, sink, 1, 0);
                    g.add_edge(copy, sink, 1, 0);
                }
                else g.add_edge(cur, sink, ones[i][j], 0);
                continue;
            }
            if(ones[i][j] == 1){
                g.add_edge(source, cur, 1, 0);
                int id = -1;
                for(int k=0;k<4;k++) if(s[i][j][k] == '1') id = k;
                for(int k=0;k<4;k++){
                    auto [c, d] = dir[k];
                    int ni = i + c, nj = j + d;
                    if(ni < 0 || ni >= n || nj < 0 || nj >= m || !ones[ni][nj]) continue;
                    add(cur, ni, nj, k^2, min( (id+4 - k)%4, (4+k - id)%4 ));
                }
            }
            else if(ones[i][j] == 2){
                int copy = cp[i][j];
                g.add_edge(source, cur, 1, 0);
                g.add_edge(source, copy, 1, 0);
                int a = s[i][j][0] == '1' ? 0 : 2;
                int b = s[i][j][1] == '1' ? 1 : 3;
                for(int k=0;k<4;k+=2){
                    auto [c, d] = dir[k];
                    int ni = i + c, nj = j + d;
                    if(ni < 0 || ni >= n || nj < 0 || nj >= m || !ones[ni][nj]) continue;
                    add(cur, ni, nj, k^2, k != a);
                }
                for(int k=1;k<4;k+=2){
                    auto [c, d] = dir[k];
                    int ni = i + c, nj = j + d;
                    if(ni < 0 || ni >= n || nj < 0 || nj >= m || !ones[ni][nj]) continue;
                    add(copy, ni, nj, k^2, k != b);
                }
            }
            else if(ones[i][j] == 3){
                g.add_edge(source, cur, 3, 0);
                int id = -1;
                for(int k=0;k<4;k++){
                    if(s[i][j][k] == '1' && s[i][j][(k+1)%4] == '1'
                        && s[i][j][(k+3)%4] == '1') id = k;
                }
                for(int k=0;k<4;k++){
                    auto [c, d] = dir[k];
                    int ni = i + c, nj = j + d;
                    if(ni < 0 || ni >= n || nj < 0 || nj >= m || !ones[ni][nj]) continue;
                    add(cur, ni, nj, k^2, min( (id+4 - k)%4, (4+k - id)%4 ));
                }
            }
            else{
                g.add_edge(source, cur, 4, 0);
                for(int k=0;k<4;k++){
                    auto [c, d] = dir[k];
                    int ni = i + c, nj = j + d;
                    if(ni < 0 || ni >= n || nj < 0 || nj >= m || !ones[ni][nj]) continue;
                    add(cur, ni, nj, k^2, 0);
                }
            }
        }
    }
    auto [f, c] = g.run(source, sink);
    ans += c;
    if(flow != 2*f) cout<<"-1\n";
    else cout<<ans<<"\n";


    return 0;
}
