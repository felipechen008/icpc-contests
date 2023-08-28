#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const vector<int> primes = {31, 37, 41};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    int m = size(primes);
    vector<vector<lint>>pot(m, vector<lint>(n));
    for(int i=0;i<m;i++){
        pot[i][0] = 1;
        lint p = primes[i];
        for(int j=1;j<n;j++) pot[i][j] = pot[i][j-1] * p % mod;
    }
    vector<int>a(n-1);
    vector<lint>one(m);
    for(int i=0;i<n-1;i++){
        cin>>a[i];
        for(int j=0;j<m;j++) one[j] += pot[j][a[i]];
    }
    for(int j=0;j<m;j++) one[j] %= mod;
    set<vector<lint>>s;
    for(int i=0;i<n;i++){
        vector<lint>cur(m);
        for(int j=0;j<m;j++) cur[j] = pot[j][i];
        s.insert(cur);
    }
    vector<vector<int>>g(n);
    for(int i=0;i<n-1;i++){
        int c, d;
        cin>>c>>d;
        c--, d--;
        g[c].push_back(d);
        g[d].push_back(c);
    }

    vector dp(n, vector<lint>(m, 1));
    auto dfs = [&](auto& self, int u, int par)->void {
        for(int v : g[u]){
            if(v == par) continue;
            self(self, v, u);
            for(int i=0;i<m;i++){
                int p = primes[i];
                dp[u][i] += dp[v][i] * p % mod;
            }
        }
        for(int i=0;i<m;i++) dp[u][i] %= mod;
    };

    dfs(dfs, 0, 0);
    vector<int>ans;

    auto reroot = [&](auto& self, int u, int par)->void {
        vector<lint>diff(m);
        for(int i=0;i<m;i++) diff[i] = (dp[u][i] - one[i] + mod) % mod;
        if(s.count(diff)) ans.push_back(u+1);
        for(int v : g[u]){
            if(v == par) continue;
            vector<lint> mu = dp[u], mv = dp[v];
            for(int i=0;i<m;i++){
                int p = primes[i];
                dp[u][i] -= dp[v][i] * p;
                dp[u][i] = (dp[u][i] % mod + mod) % mod;
                dp[v][i] += dp[u][i] * p;
                dp[v][i] = (dp[v][i] % mod + mod) % mod;
            }


            self(self, v, u);

            dp[u] = mu;
            dp[v] = mv;
        }
    };

    reroot(reroot, 0, 0);
    sort(ans.begin(), ans.end());
    cout<<size(ans)<<"\n";
    for(int u : ans) cout<<u<<" ";
    cout<<"\n";

    return 0;
}
