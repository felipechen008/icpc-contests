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
    int n;
    cin>>n;
    string s;
    cin>>s;
    int a = 0, b = 0;
    for(char c : s){
        a += c == 'o';
        b += c == 'x';
    }
    if(b || !a) cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}
