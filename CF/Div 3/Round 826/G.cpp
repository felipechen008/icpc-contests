#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        int n, m;
        cin>>n>>m;
        vector<vector<int>>g(n);
        for(int i=0;i<m;i++){
            int a, b;
            cin>>a>>b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        int f;
        cin>>f;
        vector<int>h(f);
        vector<bool>no_car(f);
        for(int i=0;i<f;i++) cin>>h[i], h[i]--;
        int k;
        cin>>k;
        vector<int>sources(k+1);
        for(int i=1;i<=k;i++) cin>>sources[i], sources[i]--, no_car[sources[i]] = 1;
        for(int i=1;i<=k;i++) sources[i] = h[sources[i]];
        vector<vector<int>>dist(k+1, vector<int>(n, inf));
        for(int z=0;z<=k;z++){
            int x = sources[z];
            dist[z][x] = 0;
            queue<int>q;
            q.push(x);
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int v : g[u]){
                    if(dist[z][v] == inf){
                        dist[z][v] = dist[z][u] + 1;
                        q.push(v);
                    }
                }
            }
        }
        vector<vector<bool>>w(n, vector<bool>(1<<k));
        for(int mask=1;mask<1<<k;mask++){
            vector<int>ind;
            for(int i=0;i<k;i++){
                if(mask>>i&1) ind.push_back(i+1);
            }
            int m = int(size(ind));
            do{
                int cur = 0;
                for(int i=0;i<m;i++){
                    int j = i == 0 ? 0 : ind[i-1];
                    int nxt = sources[ind[i]];
                    cur += dist[j][nxt];
                }
                for(int i=0;i<n;i++){
                    if(dist[0][i] == dist[ind[m-1]][i] + cur) w[i][mask] = 1;
                }

            } while(next_permutation(ind.begin(), ind.end()));
        }

        vector<bool>dp(1<<k);
        dp[0] = 1;
        for(int i=0;i<f;i++){
            if(no_car[i]) continue;
            int ver = h[i];
            vector<bool>ndp = dp;
            for(int j=0;j<1<<k;j++){
                if(!dp[j]) continue;
                for(int l=0;l<1<<k;l++){
                    if(!w[ver][l]) continue;
                    ndp[j | l] = 1;
                }
            }
            swap(dp, ndp);
        }
        int ans = k;
        for(int i=0;i<1<<k;i++){
            int b = __builtin_popcount(i);
            if(dp[i]){
                ans = min(ans, k - b);
            }
        }
        cout<<ans<<"\n";

    }
    return 0;
}
