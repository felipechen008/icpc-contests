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
    int a, b, c, d;
    cin>>a>>b>>c>>d;
    int l = max(a, c), r = min(b, d);
    if(l > r) cout<<"0\n";
    else cout<<r - l<<"\n";
    return 0;
}
