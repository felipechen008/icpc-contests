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
        int X = -1, Y = -1;
        int tot = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(s[i][j] == 'V') X = i, Y = j;
                if(s[i][j] == '.') tot++;
            }
        }
        vector<vector<int>>d(n, vector<int>(m, inf));
        vector<int>dx = {0, 1, 0, -1};
        vector<int>dy = {1, 0, -1, 0};
        {
            queue<pair<int, int>>q;
            d[X][Y] = 0;
            q.push({X, Y});

            while(!q.empty()){
                auto [x, y] = q.front();
                q.pop();
                for(int k=0;k<4;k++){
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m || s[nx][ny] == '#' || d[nx][ny] != inf) continue;
                    d[nx][ny] = d[x][y] + 1;
                    q.push({nx, ny}); 
                }
            }
        }
        
        int cnt = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(0 < i && i < n-1 && 0 < j && j < m-1) continue;
                cnt += d[i][j] != inf;
            }
        }
        if(cnt == 0) cout<<tot<<"\n";
        else if(cnt == 1){
            for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                    if(0 < i && i < n-1 && 0 < j && j < m-1) continue;
                    if(d[i][j] != inf) cout<<tot - d[i][j]<<"\n";
                }
            }
        }
        else{
            queue<array<int, 3>>q;
            vector<vector<pair<int, int>>>d1(n, vector<pair<int, int>>(m, {inf, inf}));
            vector<vector<pair<int, int>>>d2(n, vector<pair<int, int>>(m, {inf, inf}));
            int ans = inf;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(0 < i && i < n-1 && 0 < j && j < m-1) continue;
                    if(s[i][j] == '#') continue;
                    d1[i][j] = {0, i*m + j};
                    q.push({0, i, j});
                }
            }
            while(!q.empty()){
                auto [t, x, y] = q.front();
                q.pop();
                for(int k=0;k<4;k++){
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m || s[nx][ny] == '#') continue;
                    if(d1[nx][ny].st == inf){
                        if(!t) d1[nx][ny] = {d1[x][y].st + 1, d1[x][y].nd};
                        else d1[nx][ny] = {d2[x][y].st + 1, d2[x][y].nd};
                        q.push({0, nx, ny});
                    }
                    else if(d2[nx][ny].st == inf){
                        if(!t){
                            if(d1[nx][ny].nd != d1[x][y].nd) d2[nx][ny] = {d1[x][y].st + 1, d1[x][y].nd}, q.push({1, nx, ny});
                        }
                        else{
                            if(d1[nx][ny].nd != d2[x][y].nd) d2[nx][ny] = {d2[x][y].st + 1, d2[x][y].nd}, q.push({1, nx, ny});
                        }
                    }
                }
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(d1[i][j].st < inf && d2[i][j].st < inf && d[i][j] < inf){
                        ans = min(ans, d1[i][j].st + d2[i][j].st + d[i][j]);
                    }
                }
            }
            cout<<tot - ans<<"\n";
        }
    }
    return 0;
}
