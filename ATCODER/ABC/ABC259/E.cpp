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
    int n;
    cin>>n;
    vector<int>sz(n);
    vector<vector<pair<int, int>>>fac(n);
    for(int i=0;i<n;i++){
        cin>>sz[i];
        fac[i].resize(sz[i]);
        for(auto& [a, b] : fac[i]) cin>>a>>b;
    }
    map<int, int>val;
    map<int, int>f;
    for(int i=0;i<n;i++){
        for(auto [p, e] : fac[i]) val[p] = max(val[p], e);
    }
    for(int i=0;i<n;i++){
        for(auto [p, e] : fac[i]) if(val[p] == e) f[p]++;
    }
    int ans = 0;
    for(int i=0;i<n;i++){
        bool ok = false;
        for(auto [p, e] : fac[i]) if(val[p] == e && f[p] == 1) ok = true; 
        if(ok) ans++;
    }
    if(ans < n) ans++;
    cout<<ans<<"\n";

    return 0;
}
