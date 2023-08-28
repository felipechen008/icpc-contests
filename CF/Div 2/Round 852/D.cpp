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
    vector<int>p(n), q(n);
    vector<int>ip(n), iq(n);
    for(int i=0;i<n;i++) cin>>p[i], p[i]--, ip[p[i]] = i;
    for(int i=0;i<n;i++) cin>>q[i], q[i]--, iq[q[i]] = i;
    for(int i=0;i<n;i++) if(ip[i] > iq[i]) swap(ip[i], iq[i]);
    lint ans = 1;
    auto add = [&](int x, int y)->void {
        if(x > y) return;
        lint sz = (y - x + 1);
        ans += sz * (sz + 1) / 2;
    };
    add(0, ip[0] - 1);
    add(ip[0] + 1, iq[0] - 1);
    add(iq[0] + 1, n - 1);
    int mn = ip[0], mx = iq[0];
    for(int i=1;i<n;i++){
        if(ip[i] < mn && iq[i] > mx){
            ans += lint(1) * (mn - ip[i]) * (iq[i] - mx);
        }
        else if(ip[i] > mx){
            ans += lint(1) * (mn + 1) * (ip[i] - mx);

        }
        else if(iq[i] < mn){
            ans += lint(1) * (mn - iq[i]) * (n - mx);
        }
        mn = min(mn, ip[i]);
        mx = max(mx, iq[i]);
    }
    cout<<ans<<"\n";
    return 0;
}
