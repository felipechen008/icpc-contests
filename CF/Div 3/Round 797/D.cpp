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
        int n, k;
        cin>>n>>k;
        string s;
        cin>>s;
        vector<int>pref(n+1);
        for(int i=0;i<n;i++) pref[i+1] = pref[i] + (s[i] == 'W');
        int ans = inf;
        for(int i=k;i<=n;i++){
            ans = min(ans, pref[i] - pref[i-k]);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
