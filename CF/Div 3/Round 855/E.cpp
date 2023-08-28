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
    int t_;
    cin>>t_;
    while(t_--){
        int n, k;
        cin>>n>>k;
        string s, t;
        cin>>s>>t;
        vector<int>f(26), g(26);
        for(char c : s) f[c - 'a']++;
        for(char c : t) g[c - 'a']++;
        bool ok = true;
        for(int i=0;i<26;i++){
            if(f[i] != g[i]) ok = false;
        }
        if(k >= n){
            for(int i=0;i<n;i++) if(s[i] != t[i]) ok = false;
        }
        else if(k + k > n){
            int j = n - k;
            for(int i=j;i<k;i++) if(s[i] != t[i]) ok = false;
        }
        if(ok) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
