#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  string s;
  cin>>s;
  int n = int(size(s));
  int z;
  cin>>z;
  while(z--){
    string t;
    cin>>t;
    int m = int(size(t));
    vector dp(n+1, vector<bool>(m+1));
    dp[0][0] = 1;
    for(int i=0;i<n;i++){
      for(int j=0;j<=m;j++){
        if(!dp[i][j]) continue;
        if(s[i] == '*') dp[i+1][j] = 1;

        if(j < m){
          if(s[i] == '*') dp[i][j+1] = 1;
          else if(s[i] == t[j]) dp[i+1][j+1] = 1;
        }
        
      }
    }
    if(dp[n][m]) cout<<t<<"\n";
  }

  return 0;
}