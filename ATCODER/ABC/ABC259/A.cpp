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
    int n, m, x, t, d;
    cin>>n>>m>>x>>t>>d;
    t -= x * d;
    t += min(m, x) * d;
    cout<<t<<"\n";
    return 0;
}
