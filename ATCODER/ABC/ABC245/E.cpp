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
    int n, m;
    cin>>n>>m;
    vector<int>a(n), b(n), c(m), d(m);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    for(int i=0;i<m;i++) cin>>c[i];
    for(int i=0;i<m;i++) cin>>d[i];
    vector<array<int, 3>>e;
    for(int i=0;i<n;i++) e.push_back({a[i], b[i], 0});
    for(int i=0;i<m;i++) e.push_back({c[i], d[i], 1});
    sort(e.rbegin(), e.rend());
    map<int, int>f;
    for(auto [_, y, z] : e){
        if(z) f[y]++;
        else{
            auto it = f.lower_bound(y);
            if(it == f.end()){
                cout<<"No\n";
                return 0;
            }
            it->nd--;
            if(!it->nd) f.erase(it);
        }
    }
    cout<<"Yes\n";
    return 0;
}
