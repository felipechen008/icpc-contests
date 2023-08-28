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
    vector a(n, vector<int>(n));
    vector b(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cin>>a[i][j];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cin>>b[i][j];
    }

    int ans = 0;
    for(int k=0;k<4;k++){
        int cnt = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cnt += (a[i][j] && !b[i][j]);
            }
        }
        ans += !cnt;
        vector c(n, vector<int>(n));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                c[j][n-1-i] = a[i][j];
            }
        }
        swap(a, c);
    }
    if(ans) cout<<"Yes\n";
    else cout<<"No\n";


    return 0;
}
