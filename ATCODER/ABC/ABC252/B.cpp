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
    int n, k;
    cin>>n>>k;
    vector<int>a(n), b(k);
    vector<bool>w(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<k;i++) cin>>b[i], b[i]--, w[b[i]] = 1;
    vector<pair<int, int>>v(n);
    for(int i=0;i<n;i++) v[i] = {a[i], i};
    sort(v.rbegin(), v.rend());
    int ans = 0;
    for(int i=0;i<n;i++){
        if(v[i].st == v[0].st){
            ans += w[v[i].nd];
        }
    }
    if(!ans) cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}
