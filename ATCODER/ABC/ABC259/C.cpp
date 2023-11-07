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
    string s, t;
    cin>>s>>t;
    char last = '0';
    bool ok = true;
    for(int l=0,r=0;l<(int)s.size();){
        if(r == (int)t.size()){
            ok = false;
            break;
        }
        if(last != s[l]){
            last = s[l];
            if(t[r] != s[l]){
                ok = false;
                break;
            }
            l++, r++;
        }
        else{
            int x = 0, y = 0;
            while(l < (int)s.size() && s[l] == last) l++, x++;
            while(r < (int)t.size() && t[r] == last) r++, y++;
            if(x > y){
                ok = false;
                break;
            }
        }
        if(l == (int)s.size() && r != (int)t.size()) ok = false;
    }
    if(ok) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}
