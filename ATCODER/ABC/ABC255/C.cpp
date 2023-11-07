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
    lint x, a, d, n;
    cin>>x>>a>>d>>n;
    if(d < 0) x = -x, a = -a, d = -d;
    if(x <= a) cout<<(a - x)<<"\n";
    else if(x >= a + (n - 1) * d) cout<<(x - a - (n - 1) * d)<<"\n";
    else{
        lint r = (x - a) % d;
        cout<<min(r, d - r)<<"\n";
    }
}