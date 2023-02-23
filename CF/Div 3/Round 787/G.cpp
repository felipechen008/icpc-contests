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
    int n, m;
    cin>>n>>m;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector dp(m+1, vector<int>(2*m+1, inf));
    dp[m][m] = 0;
    for(int i=0;i<n;i++){
        vector ndp(m+1, vector<int>(2*m+1, inf));
        vector<int>aux(2*m+1, inf);
        for(int j=m;j>=0;j--){
            for(int k=0;k<=2*m;k++) aux[k] = min(aux[k], dp[j][k]);
            for(int k=0;k<=2*m;k++){
                int r = j + k - a[i];
                if(0 <= r && r <= 2*m) ndp[j][k] = min(ndp[j][k], aux[r] + abs(k - m));
            }
        }
        swap(dp, ndp);
    }
    int ans = inf;
    for(int i=0;i<=m;i++){
        ans = min(ans, dp[i][m]);
    }
    cout<<ans<<"\n";

    return 0;
}
