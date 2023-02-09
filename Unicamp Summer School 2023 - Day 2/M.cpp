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
    string a, b;
    cin>>a>>b;
    int x = 0, y = 0;
    for(auto c : a) x += c == 'S';
    for(auto c : b) y += c == 'S';
    for(int i=0;i<x*y;i++) cout<<"S(";
    cout<<"0";
    for(int i=0;i<x*y;i++) cout<<")";
    cout<<"\n";
    return 0;
}
