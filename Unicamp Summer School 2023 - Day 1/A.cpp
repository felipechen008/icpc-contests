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
  int n;
  cin>>n;
  vector<string>s(n);
  for(int i=0;i<n;i++) cin>>s[i];
  
  {
    vector vis(n, vector<bool>(n));
    auto dfs = [&](auto &self, int x, int y)->void {
      vis[x][y] = 1;
      for(auto [a, b] : vector<pair<int, int>>({{0, 1}, {1, 0}})){
        int nx = x + a, ny = y + b;
        if(nx < 0 || nx >= n || ny < 0 || ny >=n || vis[nx][ny] || s[nx][ny] == '#') continue;
        self(self, nx, ny);
      }
    };
    dfs(dfs, 0, 0);

    if(!vis[n-1][n-1]){
      vector vis2(n, vector<bool>(n));
      auto dfs2 = [&](auto &self, int x, int y)->void {
        vis2[x][y] = 1;
        for(auto [a, b] : vector<pair<int, int>>({{0, 1}, {1, 0}, {0, -1}, {-1, 0}})){
          int nx = x + a, ny = y + b;
        if(nx < 0 || nx >= n || ny < 0 || ny >=n || vis2[nx][ny] || s[nx][ny] == '#') continue;
          self(self, nx, ny);
        }
      };
      dfs2(dfs2, 0, 0);
      if(vis2[n-1][n-1]) cout<<"THE GAME IS A LIE\n";
      else cout<<"INCONCEIVABLE\n";
      return 0;
    }
  }
  

  vector dp(n, vector<lint>(n));
  dp[0][0] = 1;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(i < n-1 && s[i+1][j] == '.') dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % mod; 
      if(j < n-1 && s[i][j+1] == '.') dp[i][j+1] = (dp[i][j+1] + dp[i][j]) % mod;
    }
  }
  cout<<dp[n-1][n-1]<<"\n";

  return 0;
}