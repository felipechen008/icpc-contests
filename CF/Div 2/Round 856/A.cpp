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
        cin>>n;
        string a, b;
        string c, d;
        for(int i=0;i<2*n-2;i++){
            string s;
            cin>>s;
            if(size(s) == n-1){
                if(a.empty()) a = s;
                else b = s;
            }
            if(size(s) == 1){
                if(c.empty()) c = s;
                else d = s;
            }
        }
        string ans;
        if(a + c == d + b) ans = a + c;
        if(a + d == c + b) ans = a + d;
        if(c + a == b + d) ans = c + a;
        if(d + a == b + c) ans = d + a;
        int cnt = 0;
        for(int i=0;i<n;i++) cnt += ans[i] != ans[n-1-i];
        if(cnt) cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}
