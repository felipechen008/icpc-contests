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
        string s;
        cin>>s;
        int cnt = 0;
        for(char c : s) cnt += c == '1';
        int ans = 0;
        for(char c : s){
            cnt -= c == '1';
            if(!cnt) ans++;
            if(c == '0') break;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
