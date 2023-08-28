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
    string s;
    cin>>s;
    vector<string>t(n);
    for(int i=0;i<n;i++) cin>>t[i];

    int cnt = 0;
    {
        bitset<110>b;
        vector<bitset<110>>c(n);
        for(int i=0;i<m;i++) b[i] = s[i] - '0';
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++) c[i][j] = t[i][j] - '0';
        }
        vector<vector<bool>>w(n, vector<bool>(m));
        for(int j=0;j<m;j++){
            for(int i=0;i<n;i++){
                auto d = b & c[i];
                if(d.count()) w[i][j] = 1;
            }
            if(b[0]) b[m] = 1;
            b >>= 1;
        }
        vector<int>dx = {0, 1, 0, -1};
        vector<int>dy = {1, 0, -1, 0};
        vector<vector<bool>>vis(n, vector<bool>(m));
        auto dfs = [&](auto& self, int x, int y)->void {
            vis[x][y] = 1;
            for(int k=0;k<4;k++){
                int nx = x + dx[k], ny = y + dy[k];
                ny = (ny + m) % m;
                if(nx < 0 || nx >= n || vis[nx][ny] || w[nx][ny]) continue;
                self(self, nx, ny);
            }
        };

        for(int j=0;j<m;j++) if(!w[0][j] && !vis[0][j]) dfs(dfs, 0, j);
        for(int j=0;j<m;j++) cnt += vis[n-1][j];
    }

    {
        reverse(s.begin(), s.end());
        bitset<110>b;
        vector<bitset<110>>c(n);
        for(int i=0;i<m;i++) b[i] = s[i] - '0';
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++) c[i][j] = t[i][j] - '0';
        }
        vector<vector<bool>>w(n, vector<bool>(m));
        for(int j=0;j<m;j++){
            for(int i=0;i<n;i++){
                auto d = b & c[i];
                if(d.count()) w[i][j] = 1;
            }
            if(b[0]) b[m] = 1;
            b >>= 1;
        }
        vector<int>dx = {0, 1, 0, -1};
        vector<int>dy = {1, 0, -1, 0};
        vector<vector<bool>>vis(n, vector<bool>(m));
        auto dfs = [&](auto& self, int x, int y)->void {
            vis[x][y] = 1;
            for(int k=0;k<4;k++){
                int nx = x + dx[k], ny = y + dy[k];
                ny = (ny + m) % m;
                if(nx < 0 || nx >= n || vis[nx][ny] || w[nx][ny]) continue;
                self(self, nx, ny);
            }
        };

        for(int j=0;j<m;j++) if(!w[0][j] && !vis[0][j]) dfs(dfs, 0, j);
        for(int j=0;j<m;j++) cnt += vis[n-1][j];
    }

    if(cnt) cout<<"Y\n";
    else cout<<"N\n";

    return 0;
}
