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
        int n;
        string s;
        cin>>n>>s;
        for(int i=0;i<n;i++) if('A' <= s[i] && s[i] <= 'Z') s[i] += 32;
        char last = '0';
        string pat = "meow", ans;
        for(int i=0;i<n;i++){
            if(s[i] != last) ans += s[i];
            last = s[i];
        }
        if(ans != pat) cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}
