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
        int n, k;
        cin>>n>>k;
        vector<lint>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        vector<vector<lint>>dp(n+1, vector<lint>(30, -linf));
        dp[0][0] = 0;
        for(int i=0;i<n;i++){
            for(int b=0;b<30;b++){
                dp[i+1][b] = max(dp[i+1][b], dp[i][b] + (a[i]>>b) - k);
                if(b+1 < 30) dp[i+1][b+1] = max(dp[i+1][b+1], dp[i][b] + (a[i]>>(b+1)));
                else dp[i+1][b] = max(dp[i+1][b], dp[i][b]);
            }
        }
        lint ans = 0;
        for(int b=0;b<30;b++) ans = max(ans, dp[n][b]);
        cout<<ans<<"\n";

    }
    return 0;
}
