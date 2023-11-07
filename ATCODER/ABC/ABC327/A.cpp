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
    int ans = 0;
    for(int i=0;i<n-1;i++){
        ans += s[i] == 'a' && s[i+1] == 'b';
        ans += s[i] == 'b' && s[i+1] == 'a';
    }
    if(ans) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}
