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
    vector<string>s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    map<string, int>f;
    for(int i=0;i<n;i++){
        if(f.count(s[i])){
            cout<<s[i]<<"("<<f[s[i]]<<")\n";
            f[s[i]]++;
        }
        else{
            cout<<s[i]<<"\n";
            f[s[i]] = 1;
        }
    }
    return 0;
}
