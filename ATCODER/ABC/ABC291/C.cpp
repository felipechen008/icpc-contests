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
    string s;
    cin>>n>>s;
    set<pair<int, int>>t;
    int x = 0, y = 0;
    t.insert({x, y});
    for(char c : s){
        if(c == 'R') x++;
        if(c == 'L') x--;
        if(c == 'U') y++;
        if(c == 'D') y--;
        t.insert({x, y});
    }
    if(int(size(t)) == n + 1) cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}
