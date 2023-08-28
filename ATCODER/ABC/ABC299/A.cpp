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
    int l = -1, r = -1, m = -1;
    for(int i=0;i<n;i++){
        if(s[i] == '*') m = i;
        if(s[i] == '|'){
            if(l == -1) l = i;
            else r = i;
        }
    }
    if(l < m && m < r) cout<<"in\n";
    else cout<<"out\n";
    return 0;
}
