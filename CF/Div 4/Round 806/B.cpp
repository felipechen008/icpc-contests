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
        string s;
        cin>>s;
        vector<int>f(26);
        for(char c : s) f[c - 'A']++;
        int ans = n;
        for(int i=0;i<26;i++) ans += (f[i] > 0);
        cout<<ans<<"\n"; 
    }
    return 0;
}
