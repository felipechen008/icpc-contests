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
    int n, x, y, z;
    cin>>n>>x>>y>>z;
    vector<int>a(n), b(n);
    vector<pair<int, int>>c(n), d(n), e(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    for(int i=0;i<n;i++){
        c[i] = {-a[i], i};
        d[i] = {-b[i], i};
        e[i] = {-a[i] - b[i], i};
    }
    sort(c.begin(), c.end());
    sort(d.begin(), d.end());
    sort(e.begin(), e.end());
    vector<bool>w(n);
    for(int i=0,j=0;j<x;i++){
        auto [_, id] = c[i];
        if(w[id]) continue;
        w[id] = 1;
        j++;
    }
    for(int i=0,j=0;j<y;i++){
        auto [_, id] = d[i];
        if(w[id]) continue;
        w[id] = 1;
        j++;
    }
    for(int i=0,j=0;j<z;i++){
        auto [_, id] = e[i];
        if(w[id]) continue;
        w[id] = 1;
        j++;
    }
    for(int i=0;i<n;i++) if(w[i]) cout<<i+1<<"\n";

    return 0;
}
