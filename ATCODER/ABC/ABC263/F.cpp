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
    vector<vector<int>>c(1<<n, vector<int>(n));
    for(int i=0;i<1<<n;i++){
        for(int j=0;j<n;j++) cin>>c[i][j];
    }
    vector<vector<lint>>dp(n + 1, vector<lint>(1<<n));
    for(int i=1;i<=n;i++){
        for(int j=0;j<1<<n;j++) dp[i][j] = c[j][i-1];
    }
    for(int k=1;k<=n;k++){
        vector<vector<lint>>cur(n + 1, vector<lint>(1<<(n-k)));
        for(int i=k;i<=n;i++){
            for(int j=0;j<(1<<(n-k));j++){
                cur[i][j] = max(dp[i][2*j] + dp[k-1][2*j+1], 
                                dp[k-1][2*j] + dp[i][2*j+1]);
            }
        }
        swap(dp, cur);
    }
    cout<<dp[n][0]<<"\n";
    return 0;
}
