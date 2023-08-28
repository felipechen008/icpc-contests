#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct bipartite_matching {
    int N, M, T;
    vector<vector<int>> adj;
    vector<int> match, seen;
    bipartite_matching(int a, int b) : N(a), M(a + b), adj(M), 
            match(M, -1), seen(M, -1), T(0) {}
    void add_edge(int a, int b) {
        assert(0 <= a && a < N && b + N < M && N <= b + N);
        adj[a].push_back(b + N);
    }
    void shuffle_edges() { // useful to break some hairy tests
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        for (auto& cur : adj)
            shuffle(cur.begin(), cur.end(), rng);
    } 
    bool dfs(int cur) {
        if (seen[cur] == T) return false;
        seen[cur] = T;
        for (int nxt : adj[cur]) 
            if (match[nxt] == -1) {
                match[nxt] = cur, match[cur] = nxt;
                return true;
            }
        for (int nxt : adj[cur]) 
            if (dfs(match[nxt])) {
                match[nxt] = cur, match[cur] = nxt;
                return true;
            }
        return false;
    }
    int solve() {
        int res = 0;
        while (true) {
            int cur = 0; ++T;
            for (int i = 0; i < N; ++i) 
                if (match[i] == -1) cur += dfs(i);
            if (cur == 0) break;
            else res += cur;
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin>>n;
    vector<vector<int>>g1(n);
    for(int i=1;i<n;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g1[a].push_back(b);
        g1[b].push_back(a);
    }
    cin>>m;
    vector<vector<int>>g2(m);
    for(int i=1;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g2[a].push_back(b);
        g2[b].push_back(a);
    }

    if(n < m){
        cout<<"N\n";
        return 0;
    }

    vector<int>h2(m);


    {
        auto dfs = [&](auto& self, int u, int p)->void {
            for(int v : g2[u]){
                if(v == p) continue;
                h2[v] = h2[u] + 1;
                self(self, v, u);
            }
        };

        dfs(dfs, 0, 0);
    }

    vector<vector<int>>ind2(m);
    for(int i=0;i<m;i++) ind2[h2[i]].push_back(i);

    auto solve = [&](int root)->bool {
        
        vector<int>h1(n);

        auto dfs = [&](auto& self, int u, int p)->void {
            for(int v : g1[u]){
                if(v == p) continue;
                h1[v] = h1[u] + 1;
                self(self, v, u);
            }
        };

        dfs(dfs, root, root);

        vector<vector<int>>ind1(n);
        for(int i=0;i<n;i++) ind1[h1[i]].push_back(i);

        vector<vector<bool>>w(n, vector<bool>(m));
        for(int z=m-1;z>=0;z--){
            for(int u : ind1[z]){
                for(int v : ind2[z]){
                    int su = int(size(g1[u]));
                    int sv = int(size(g2[v]));
                    bipartite_matching g(su, sv);
                    for(int i=0;i<su;i++){
                        for(int j=0;j<sv;j++){
                            int r = g1[u][i], s = g2[v][j];
                            if(w[r][s]) g.add_edge(i, j);
                        }
                    }
                    int cnt = sv - (z != 0);
                    if(g.solve() == cnt) w[u][v] = 1;
                }
            }
        }
        return w[root][0];
    };

    for(int i=0;i<n;i++){
        if(solve(i)){
            cout<<"Y\n";
            return 0;
        }
    }

    cout<<"N\n";

    return 0;
}
