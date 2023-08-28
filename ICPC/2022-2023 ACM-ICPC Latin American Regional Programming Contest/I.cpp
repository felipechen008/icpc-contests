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
    int r, c;
    cin>>r>>c;
    vector a(r, vector<int>(c));
    vector<pair<int, int>>pos(r * c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++) cin>>a[i][j], a[i][j]--, pos[a[i][j]] = {i, j};
    }
    vector<int>dx = {0, 0, 1, -1};
    vector<int>dy = {1, -1, 0, 0};

    vector<bool>w(r * c);
    int ans = 0;
    for(int i=0;i<r * c;i++){
        if(w[i]) continue;
        w[i] = 1;
        vector vis(r, vector<bool>(c));
        int cnt = 1;
        {
            auto [x, y] = pos[i];
            vis[x][y] = 1;
        }
        for(int j=i+1;j<r*c;j++){
            auto [x, y] = pos[j];
            int con = 0;
            for(int k=0;k<4;k++){
                int nx = x + dx[k], ny = y + dy[k];
                if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
                con += vis[nx][ny];
            }
            if(con) cnt++, vis[x][y] = 1, w[j] = 1;
        }
        ans = max(ans, cnt);
    }
    cout<<ans<<"\n";
    return 0;
}
