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
    int ans = inf;
    for(int i=0;i<10;i++){
        vector<int>f(10);
        int cur = 0;
        for(int j=0;j<n;j++){
            for(int k=0;k<10;k++){
                if(s[j][k] == '0' + i){
                    cur = max(cur, f[k] + k);
                    f[k] += 10;
                    break;
                }
            }
        }
        ans = min(ans, cur);
    }
    cout<<ans<<"\n";
    return 0;
}
