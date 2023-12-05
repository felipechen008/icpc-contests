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
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector dp(n+1, vector(n+1, vector(51, vector(51, int(0)))));
    for(int x=0;x<n;x++){
        for(int i=0;i+x<n;i++){
            int j = i + x;
            for(int y=0;y<50;y++){
                for(int l=1;l+y<=50;l++){
                    int r = l + y;
                    dp[i][j][l][r] = max(dp[i][j][l][r], dp[i][j][l][r-1]);
                    for(int k=i;k<=j;k++){
                        if(a[k] == r){
                            for(int m=l;m<=r;m++){
                                dp[i][j][l][r] = max(dp[i][j][l][r], 1 + 
                            (k > 0 ? dp[i][k-1][l][m] : 0) + dp[k+1][j][m][r]);
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<dp[0][n-1][1][50]<<"\n";
   return 0;
    return 0;
}
