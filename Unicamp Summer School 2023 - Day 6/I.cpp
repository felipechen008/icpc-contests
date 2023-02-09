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
    vector<int>a(n);
    int cnt = 0;
    for(int i=0;i<n;i++) cin>>a[i], cnt ^= a[i];
    if(cnt&1) cout<<"John\n";
    else cout<<"Preston\n";
    return 0;
}
