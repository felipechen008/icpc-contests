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
    string s, t;
    cin>>s>>t;
    int m = (int)t.size();
    int n;
    cin>>n;
    vector<char>c(n);
    vector<string>a(n);
    for(int i=0;i<n;i++) cin>>c[i]>>a[i];
    vector<vector<int>>g(26, vector<int>(26, inf));
    for(int i=0;i<26;i++) g[i][i] = 0;
    for(int i=0;i<n;i++) if(a[i].size() == 1) g[c[i] - 'a'][a[i][0] - 'a'] = 1;
    for(int k=0;k<26;k++){
        for(int i=0;i<26;i++){
            for(int j=0;j<26;j++) g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        }
    }
    // dp[l][r][c] min cost to construct l, r starting with character c
    vector dp(m, vector(m, vector(26, int(inf))));
    for(int i=0;i<m;i++){
        for(int ch=0;ch<26;ch++){
            dp[i][i][ch] = g[ch][t[i] - 'a'];
        }
    }
    for(int j=0;j<n;j++){
        int sz = (int)a[j].size();
        for(int i=0;i+sz<=m;i++){
            int cur = 0;
            for(int k=0;k<sz;k++) cur += t[i+k] != a[j][k];
            if(!cur){
                for(int ch=0;ch<26;ch++) dp[i][i+sz-1][ch] = min(dp[i][i+sz-1][ch], 1 + g[ch][c[j] - 'a']);
            }
        }
    }
    for(int z=2;z<=m;z++){
        for(int i=0;i+z<=m;i++){
            int l = i, r = i + z - 1;
            for(int j=0;j<n;j++){
                int sz = (int)a[j].size();
                if(z < sz) continue;
                vector memo(z+1, vector(sz+1, int(inf)));
                memo[0][0] = 0;
                for(int x=0;x<z;x++){
                    for(int y=0;y<sz;y++){
                        for(int k=0;k<=z-x-sz+y;k++){
                            memo[x+k+1][y+1] = min(memo[x+k+1][y+1], memo[x][y] + dp[l+x][l+x+k][a[j][y] - 'a']);
                        }
                    }
                }
                for(int ch=0;ch<26;ch++) dp[l][r][ch] = min(dp[l][r][ch], memo[z][sz] + g[ch][c[j] - 'a'] + 1);
            }
        }
    }
    int sz = (int)s.size();
    vector ans(m+1, vector(sz+1, int(inf)));
    ans[0][0] = 0;
    for(int x=0;x<m;x++){
        for(int y=0;y<sz;y++){
            for(int k=0;k<=m-x-sz+y;k++){
                ans[x+k+1][y+1] = min(ans[x+k+1][y+1], ans[x][y] + dp[x][x+k][s[y] - 'a']);
            }
        }
    }
    if(ans[m][sz] == inf) cout<<"-1\n";
    else cout<<ans[m][sz]<<"\n";
    return 0;
}
