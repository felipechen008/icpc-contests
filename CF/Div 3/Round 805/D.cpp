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
        int p;
        cin>>s>>p;
        vector<int>f(26), g(26);
        for(char c : s) f[c - 'a']++;
        for(int i=0;i<26;i++){
            int j = i+1;
            int k = min(f[i], p / j);
            g[i] = k;
            p -= k * j;
        }
        for(char c : s){
            if(g[c - 'a']) g[c - 'a']--, cout<<c;
        }
        cout<<"\n";
    }
    return 0;
}
