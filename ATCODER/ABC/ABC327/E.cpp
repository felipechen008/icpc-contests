#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;
using dbl = double;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    const dbl c = 0.9;
    vector<dbl>p(n);
    for(int i=0;i<n;i++) cin>>p[i];
    vector<dbl>dp(n+1);
    for(int i=0;i<n;i++){
        dp[i+1] = dp[i] * c + p[i];
        for(int j=i-1;j>=0;j--){
            dp[j+1] = max(dp[j+1], dp[j] * c + p[i]);
        }
    }
    dbl ans = -1200, cnt = 1;
    cout<<fixed<<setprecision(10);
    for(int i=1;i<=n;i++){
        ans = max(ans, dp[i] / cnt - 1200.0 / sqrt(dbl(i)));
        cnt = cnt * c + 1.0;
    }
    cout<<ans<<"\n";
    return 0;
}
