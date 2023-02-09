#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int lim = 12010;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    lint k;
    cin>>n>>m>>k;
    vector<vector<int>>a(n, vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }
    vector dp(n, vector(m, vector<lint>(lim)));

    dp[n-1][m-1][a[n-1][m-1]] = 1;
    for(int i=n-1;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            for(int l=0;l<lim;l++){
                if(i && l + a[i-1][j] < lim){
                    dp[i-1][j][l+a[i-1][j]] += dp[i][j][l];
                }
                if(j && l + a[i][j-1] < lim){
                    dp[i][j-1][l+a[i][j-1]] += dp[i][j][l];
                }
            }
        }
    }
    int id = -1;
    for(int i=lim-1;i>=0;i--){
        if(dp[0][0][i] >= k){
            id = i;
            break;
        }
        k -= dp[0][0][i];
    }

    int x = 0, y = 0, z = id;
    string ans;
    for(int i=0;i<n+m-2;i++){
        z -= a[x][y];
        if(x < n-1){
            if(dp[x+1][y][z] >= k) x++, ans += 'D';
            else k -= dp[x+1][y][z], y++, ans += 'R';
        }
        else y++, ans += 'R';
    }
    cout<<ans<<"\n";


    return 0;
}
