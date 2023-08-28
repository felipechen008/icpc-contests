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
    int n, k, e;
    cin>>n>>k>>e;
    int x = e, y = n - k - e;
    if(x > y) swap(x, y);
    vector<bitset<1010>>dp(x + 1);
    dp[0][0] = 1;
    for(int i=1;i<=n;i++){
        if(i == k) continue;
        for(int a=x;a>=0;a--){
            if(a + i <= x) dp[a + i] |= dp[a];
            dp[a] |= dp[a] << i;
        }        
    } 
    int ans = inf;
    for(int i=0;i<=x;i++){
        for(int j=0;j<=y;j++){
            if(dp[i][j]) ans = min(ans, x + y - (i + j));
        }
    }
    cout<<ans<<"\n";

    return 0;
}
