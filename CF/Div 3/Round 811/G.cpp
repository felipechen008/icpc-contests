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
        int n;
        cin>>n;
        vector<vector<array<int, 3>>>g(n);
        vector<int>p(n);
        for(int i=1;i<n;i++){
            int a, b;
            cin>>p[i]>>a>>b;
            p[i]--;
            g[p[i]].push_back({i, a, b});
        }
        vector<lint>pref(1);
        lint sum = 0;
        vector<int>ans(n-1);
        auto dfs = [&](auto& self, int u)->void {
            for(auto [v, a, b] : g[u]){
                pref.push_back(pref.back() + b);
                sum += a;
                int cnt = int(upper_bound(pref.begin(), pref.end(), sum) - pref.begin());
                ans[v-1] = cnt - 1;
                
                self(self, v);
                sum -= a;
                pref.pop_back();
            }
        };
        dfs(dfs, 0);

        for(int u : ans) cout<<u<<" ";
        cout<<"\n";
    }
    return 0;
}
