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
        cin>>s;
        int n = int(size(s));
        vector<array<int, 2>>dp(26);
        for(int i=0;i<26;i++) dp[i][1] = -inf;
        for(auto ch : s){
            int c = ch - 'a'; 
            int zero = dp[c][0], one = dp[c][1];
            dp[c][0] = max(dp[c][0], one + 1);
            dp[c][1] = max(dp[c][1], zero + 1);
            for(int i=0;i<26;i++) dp[i][0] = max(dp[i][0], dp[c][0]);
        }
        int ans = 0;
        for(int i=0;i<26;i++) ans = max(ans, dp[i][0]);
        cout<<n - ans<<"\n";
    }
    return 0;
}
