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
    string t;
    int d;
    cin>>t>>d;
    int ans = 0;
    int n = int(size(t));
    for(int i=0;i<n;){
        vector<int>f(2);
        int j = 2;
        for(;i+j<=n;j++){
            f.push_back(f.back());
            while(f[j] && t[f[j] + i] != t[j-1 + i]) f[j] = f[f[j]];
            if(t[f[j] + i] == t[j-1 + i]) f[j]++;
            if(j > d && f[j] < j - d) break;
        }
        i += j - 1;
        ans++;
    }
    cout<<ans<<"\n";
    return 0;
}
