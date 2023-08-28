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
        int n, m;
        cin>>n>>m;
        vector<string>s(n);
        for(int i=0;i<n;i++) cin>>s[i];
        vector vis(n, vector<bool>(m));
        int cnt = 0, sx = 0, sy = 0;
        auto dfs = [&](auto& self, int x, int y)->void {
            vis[x][y] = 1;
            cnt++;
            sx += x, sy += y;
            for(int i=-1;i<=1;i++){
                for(int j=-1;j<=1;j++){
                    int nx = x + i, ny = y + j;
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m || s[nx][ny] == '.' || vis[nx][ny]) continue;
                    self(self, nx, ny);
                }
            }
        };
        bool ok = true;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(s[i][j] == '.' || vis[i][j]) continue;
                cnt = sx = sy = 0;
                dfs(dfs, i, j);
                if(cnt != 3) ok = false;
                else{
                    sx /= 3, sy /= 3;
                    int num = 0;
                    for(int x=0;x<=1;x++){
                        for(int y=0;y<=1;y++){
                            int nx = x + sx, ny = y + sy;
                            if(nx < 0 || nx >= n || ny < 0 || ny >= m || s[nx][ny] == '.') continue;
                            num++;
                        }
                    }
                    if(num != 3) ok = false;
                }
            }
        }
        if(ok) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
