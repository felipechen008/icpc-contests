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
    vector<vector<int>>a(9, vector<int>(9));
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++) cin>>a[i][j], a[i][j]--;
    }
    int ans = 0;
    for(int i=0;i<9;i++){
        vector<bool>w(9);
        for(int j=0;j<9;j++) w[a[i][j]] = 1;
        for(int j=0;j<9;j++) ans += !w[j];
    }
    for(int i=0;i<9;i++){
        vector<bool>w(9);
        for(int j=0;j<9;j++) w[a[j][i]] = 1;
        for(int j=0;j<9;j++) ans += !w[j];
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            vector<bool>w(9);
            for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                    int x = 3 * i + k, y = 3 * j + l;
                    w[a[x][y]] = 1;
                }
            }
            for(int k=0;k<9;k++) ans += !w[k];
        }
    }
    if(ans) cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}
