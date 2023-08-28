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
    lint n;
    cin>>n;
    vector<lint>a(n), f(200100);
    for(int i=0;i<n;i++) cin>>a[i], f[a[i]]++;
    lint ans = n * (n - 1) * (n - 2) / 6;
    for(int i=0;i<200100;i++){
        lint c = f[i];
        ans -= c * (c - 1) * (c - 2) / 6 + c * (c - 1) / 2 * (n - c);
    }
    cout<<ans<<"\n";
    return 0;
}
