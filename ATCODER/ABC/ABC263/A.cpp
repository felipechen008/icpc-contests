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
    vector<int>v(5), f(20);
    for(int i=0;i<5;i++) cin>>v[i], f[v[i]]++;
    int a = 0, b = 0;
    for(int i=0;i<20;i++) a += f[i] == 2, b += f[i] == 3;
    if(a && b) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}
