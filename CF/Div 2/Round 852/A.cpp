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
        lint a, b, n, m;
        cin>>a>>b>>n>>m;
        lint r = n % (m + 1);
        cout<<min(b * n, a * (n / (m+1) * m) + min(b, a) * r)<<"\n";
    }
    return 0;
}
