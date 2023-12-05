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
    vector<vector<bool>>g(n, vector<bool>(n));
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a][b] = g[b][a] = 1;
    }
    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            for(int k=0;k<j;k++) ans += g[i][j] && g[j][k] && g[k][i];
        }
    }
    cout<<ans<<"\n";
    return 0;
}
