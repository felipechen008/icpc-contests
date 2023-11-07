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
    vector<lint>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a.begin(), a.end());
    vector<lint>pref(n + 1);
    for(int i=0;i<n;i++) pref[i+1] = pref[i] + a[i];
    while(q--){
        lint x;
        cin>>x;
        int u = int(lower_bound(a.begin(), a.end(), x) - a.begin());
        cout<< (x * u - pref[u]) + (pref[n] - pref[u] - (n - u) * x)<<"\n";
    }
}