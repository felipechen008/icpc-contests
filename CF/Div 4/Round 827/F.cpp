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
        int q;
        cin>>q;
        lint sa = 0, ta = 0, sb = 0, tb = 0;
        while(q--){
            int op, k;
            string s;
            cin>>op>>k>>s;
            lint a = 0, b = 0;
            for(char c : s) a += c == 'a', b += c != 'a';
            a *= k, b *= k;
            if(op == 1) sa += a, sb += b;
            else ta += a, tb += b;

            if(tb) cout<<"YES\n";
            else if(sb) cout<<"NO\n";
            else if(sa < ta) cout<<"YES\n";
            else cout<<"NO\n";  
        }
    }
    return 0;
}
