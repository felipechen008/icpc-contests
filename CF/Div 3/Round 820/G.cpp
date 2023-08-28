#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 1e9 + 7;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t_;
    cin>>t_;
    while(t_--){
        string s, t;
        cin>>s>>t;

        int n = int(size(s)), m = int(size(t));
        vector<int>f(m+1);
        for(int i=2;i<=m;i++){
            f[i] = f[i-1];
            while(f[i] && t[f[i]] != t[i-1]) f[i] = f[f[i]];
            if(t[f[i]] == t[i-1]) f[i]++; 
        }
        vector<array<int, 26>>table(m);
        for(int i=0;i<m;i++){
            for(int j=0;j<26;j++){
                if(i && t[i] - 'a' != j) table[i][j] = table[f[i]][j];
                else table[i][j] = i + (t[i] - 'a' == j);
            }
        }
        vector<bool>matches(n);
        for(int i=0,j=0;i<n;i++){
            while(j && s[i] != t[j]) j = f[j];
            if(s[i] == t[j]) j++;
            if(j == m){
                matches[i - m + 1] = 1;
                j = f[j];
            }
        }

        vector dp(n+1, vector<int>(m+1, inf));
        dp[0][0] = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matches[i]) dp[i+m][0] = min(dp[i+m][0], dp[i][j] + 1);
                int k = table[j][s[i] - 'a'];
                dp[i+1][k] = min(dp[i+1][k], dp[i][j]);
            }
        }

        int ans = inf;
        for(int j=0;j<m;j++) ans = min(ans, dp[n][j]);

        vector cnt(n+1, vector<lint>(m+1, 0));
        for(int j=0;j<m;j++) if(dp[n][j] == ans) cnt[n][j] = 1;
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<m;j++){
                if(matches[i] && dp[i+m][0] == dp[i][j] + 1) cnt[i][j] += cnt[i+m][0];
                int k = table[j][s[i] - 'a'];
                if(dp[i+1][k] == dp[i][j]) cnt[i][j] += cnt[i+1][k];
                cnt[i][j] %= mod;
            }
        }

        cout<<ans<<" "<<cnt[0][0]<<"\n";

    }
    return 0;
}
