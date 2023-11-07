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
    int n, x, y;
    cin>>n>>x>>y;
    lint a = 1, b = 0;
    for(int i=1;i<n;i++){
        lint c = a + a * x + b;
        lint d = (a * x + b) * y;
        a = c, b = d;
    }
    cout<<b<<"\n";
    return 0;
}
