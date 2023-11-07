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
    vector<int>a(n), f(8);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++){
        f[0]++;
        for(int j=3;j>=0;j--) f[j + a[i]] += f[j], f[j] = 0;
    }
    int ans = 0;
    for(int j=4;j<8;j++) ans += f[j];
    cout<<ans<<"\n";

    return 0;
}
