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
        vector<string>s(n);
        for(int i=0;i<n;i++) cin>>s[i];
        int cnt = 0;
        vector<int>dp(n);
        for(int i=0;i<n;i++){
            vector<int>ndp(n);
            for(int j=0;j<n;j++){
                int c = s[i][j] - '0';
                cnt += c;
                ndp[j] = dp[(j+n-1) % n] + c;
            }
            swap(dp, ndp);
        }
        int ans = 0;
        for(int i=0;i<n;i++) ans = max(ans, dp[i]);
        cout<<cnt + n - 2 * ans<<"\n";
    }


    return 0;
}
