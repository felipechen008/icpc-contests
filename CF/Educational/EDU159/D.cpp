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
    int n, q;
    cin>>n>>q;
    string t;
    cin>>t;
    vector<int>xs(n+1), ys(n+1);
    map<pair<int, int>, vector<int>>f;
    f[{0, 0}].push_back(0);
    int X = 0, Y = 0;
    for(int i=0;i<n;i++){
        if(t[i] == 'U') Y++;
        if(t[i] == 'D') Y--;
        if(t[i] == 'L') X--;
        if(t[i] == 'R') X++;
        xs[i+1] = X, ys[i+1] = Y;
        f[{X, Y}].push_back(i+1);
    }
    for(int i=0;i<q;i++){
        int x, y, l, r;
        cin>>x>>y>>l>>r;
        {
            auto& v = f[{x, y}];
            if(!v.empty() && (v[0] < l || v.back() > r)){
                cout<<"YES\n";
                continue;
            }
        }
        int kx = x, ky = y;
        kx -= xs[l-1], ky -= ys[l-1];
        kx = xs[r] - kx, ky = ys[r] - ky;
        auto& v = f[{kx, ky}];
        auto it = lower_bound(v.begin(), v.end(), l-1);
        if(it != v.end() && *it <= r) cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}
