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
        vector<int>p(n), pos(n);
        for(int i=0;i<n;i++) cin>>p[i], pos[p[i]] = i;
        lint ans = 0;
        int mn = pos[0], mx = pos[0];
        for(int sz=1;sz<=n;sz++){
            int cur = mx - mn + 1;
            if(cur <= sz){
                int x = sz - cur;
                int c = mn, d = n - 1 - mx;
                ans += max(0, min(c, x) - max(0, x - d) + 1);
            }
            if(sz % 2 == 0 && sz < n){
                mn = min(mn, pos[sz/2]);
                mx = max(mx, pos[sz/2]);
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
