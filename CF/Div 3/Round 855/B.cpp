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
        int n, k;
        cin>>n>>k>>s;
        vector<int>f(26), g(26);
        for(char c : s){
            if('a' <= c && c <= 'z') f[c - 'a']++;
            else g[c - 'A']++;
        }
        int ans = 0;
        for(int i=0;i<26;i++){
            int c = min(f[i], g[i]);
            f[i] -= c, g[i] -= c;
            ans += c;
            int d = (f[i] + g[i]) / 2;
            int e = min(d, k);
            k -= e;
            ans += e;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
