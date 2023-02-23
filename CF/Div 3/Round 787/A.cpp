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
        int a, b, c, x, y;
        cin>>a>>b>>c>>x>>y;
        if(x > a + c || y > b + c || x + y > a + b + c) cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}
