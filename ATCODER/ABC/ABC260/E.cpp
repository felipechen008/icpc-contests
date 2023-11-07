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
    vector<int>a(n), b(n);
    for(int i=0;i<n;i++) cin>>a[i]>>b[i], a[i]--,b[i]--;
    int mx = *max_element(a.begin(), a.end());
    vector<int>v(m);
    for(int i=0;i<n;i++) v[a[i]] = max(v[a[i]], b[i]);
    for(int i=0;i<n;i++) v[b[i]] = m;
    vector<int>pref(m+2);
    for(int l=0,r=mx;l<m;l++){
        int sz = r - l + 1;
        pref[sz]++;
        pref[m-l+1]--;
        r = max(r, v[l]);
    }
    for(int i=1;i<=m;i++) pref[i] += pref[i-1];
    for(int i=1;i<=m;i++) cout<<pref[i]<<" ";
    cout<<"\n";
    return 0;
}
