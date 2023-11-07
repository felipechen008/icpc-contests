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
    lint n, a, b;
    cin>>n>>a>>b;
    lint g = gcd(a, b), lcm = a / g * b;
    lint ans = n * (n + 1) / 2;
    lint x = n / a, y = n / b, z = n / lcm;
    ans -= a * x * (x + 1) / 2;
    ans -= b * y * (y + 1) / 2;
    ans += lcm * z * (z + 1) / 2;
    cout<<ans<<"\n";
    return 0;
}
