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
        int a, b, c;
        cin>>a>>b>>c;
        int d = (a - 1), e = abs(b - c) + (c - 1);
        if(d < e) cout<<"1\n";
        else if(d > e) cout<<"2\n";
        else cout<<"3\n";
    }
    return 0;
}
