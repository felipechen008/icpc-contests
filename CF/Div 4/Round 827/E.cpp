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
        int n, q;
        cin>>n>>q;
        vector<int>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        vector<lint>pref(n+1);
        for(int i=0;i<n;i++) pref[i+1] = pref[i] + a[i];
        vector<int>v(1), idv(1);
        for(int i=0;i<n;i++) if(a[i] > v.back() ) v.push_back(a[i]), idv.push_back(i + 1);
        idv.push_back(n+1);
        while(q--){
            int k;
            cin>>k;
            int u = int(upper_bound(v.begin(), v.end(), k) - v.begin());
            u = idv[u];
            cout<<pref[u-1]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
