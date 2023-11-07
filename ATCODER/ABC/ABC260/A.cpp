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
    string s;
    cin>>s;
    map<char, int>f;
    for(char c : s) f[c]++;
    for(auto [x, y] : f){
        if(y == 1){
            cout<<x<<"\n";
            return 0;
        }
    }
    cout<<"-1\n";
    return 0;
}
