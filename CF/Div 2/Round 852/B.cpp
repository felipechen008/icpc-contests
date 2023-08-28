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
        int x, y;
        cin>>x>>y;
        cout<<(x - y) * 2 <<"\n";
        for(int i=x;i>=y;i--) cout<<i<<" ";
        for(int i=y+1;i<x;i++) cout<<i<<" ";
        cout<<"\n";
    }
    return 0;
}
