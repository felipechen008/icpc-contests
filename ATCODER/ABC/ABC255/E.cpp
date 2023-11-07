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
    vector<lint>s(n-1), a(n);
    for(int i=0;i<n-1;i++) cin>>s[i];
    for(int i=0;i<n-1;i++) a[i+1] = s[i] - a[i];
    vector<vector<lint>>f(2);
    for(int i=0;i<n;i++) f[i&1].push_back(a[i]);
    sort(f[0].begin(), f[0].end());
    sort(f[1].begin(), f[1].end());
    vector<lint>x(m);
    for(int i=0;i<m;i++) cin>>x[i];
    set<lint>v;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            lint d = x[j] - a[i];
            if(i&1) v.insert(-d);
            else v.insert(d);
        }
    }
    int ans = 0;
    for(lint d : v){
        int cur = 0;
        for(int k=0;k<m;k++){
            cur += upper_bound(f[0].begin(), f[0].end(), x[k] - d) -
                lower_bound(f[0].begin(), f[0].end(), x[k] - d);
        
            cur += upper_bound(f[1].begin(), f[1].end(), x[k] + d) -
                lower_bound(f[1].begin(), f[1].end(), x[k] + d);
        }
        ans = max(ans, cur);
    }
    cout<<ans<<"\n";

    return 0;
}
