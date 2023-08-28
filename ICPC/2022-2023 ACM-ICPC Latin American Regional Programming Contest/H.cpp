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
    int n;
    cin>>n;
    vector<string>s(n);
    map<string, int>id;
    for(int i=0;i<n;i++) cin>>s[i], id[s[i]] = i;
    vector<int>mx(n);
    vector<vector<bool>>w(n, vector<bool>(n));
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        int m, k;
        cin>>m>>k;
        k--;
        vector<bool>f(n);
        for(int j=0;j<m;j++){
            string t;
            cin>>t;
            int ind = id[t];
            f[ind] = 1;
        }
        for(int i=0;i<n;i++){
            if(f[i]) mx[i] = max(mx[i], k);
            else w[i][k] = 1;
        }
    }
    
    bipartite_matching g(n, n);
    for(int i=0;i<n;i++){
        for(int j=mx[i];j<n;j++){
            if(!w[i][j]) g.add_edge(i, j);
        }
    }
    g.solve();
    vector<int>ans(n);
    for(int i=0;i<n;i++){
        ans[g.match[i] - n] = i;
    }
    for(int u : ans) cout<<s[u]<<" ";
    cout<<"\n";

    return 0;
}
