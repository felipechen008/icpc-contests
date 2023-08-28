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
    string s;
    cin>>s;
    int n = int(size(s));
    vector<int>last(26, n);
    vector<vector<int>>nxt(n, vector<int>(26));
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<26;j++) nxt[i][j] = last[j];
        last[s[i] - 'a'] = i;
    }
    lint ans = 0;
    for(int z=0;z<n;z++){
        vector dp(n, vector (n, lint(0)));
        int c = s[z] - 'a';
        if(last[c] >= z) continue; 
        dp[last[c]][z] = 1;
        for(int i=0;i<z;i++){
            for(int j=z;j<n;j++){
                for(int k=0;k<26;k++){
                    if(nxt[i][k] < z && nxt[j][k] < n){
                        dp[nxt[i][k]][nxt[j][k]] += dp[i][j];
                        dp[nxt[i][k]][nxt[j][k]] %= mod;
                    }
                }
                if( nxt[i][c] == z){
                    ans += dp[i][j];
                    ans %= mod;
                }
            }
        }
    }
    cout<<ans<<"\n";

    return 0;
}
