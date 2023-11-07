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
    int a, b, c;
    cin>>a>>b>>c;
    if(a <= b && b <= c) cout<<"Yes\n";
    else if(a >= b && b >= c) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}
