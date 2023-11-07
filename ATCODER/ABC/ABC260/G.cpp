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
    vector<string>s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    vector<vector<int>>add(n, vector<int>(n));
    vector<vector<int>>rem(n, vector<int>(5*n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(s[i][j] == 'O'){
                add[i][j]++;
                if(i + m < n) add[i+m][j]--;
                rem[i][j+2*m]--;
                if(i + m < n) rem[i+m][j]++;
            }
        }
    }
    for(int j=0;j<n;j++){
        for(int i=1;i<n;i++){
            add[i][j] += add[i-1][j];
        }
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<5*n-2;j++){
            rem[i][j] += rem[i-1][j+2];
        }
    }
    vector<vector<int>>ans(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) ans[i][j] += ans[i][j-1] + add[i][j] + rem[i][j];
    }
    int q;
    cin>>q;
    while(q--){
        int x, y;
        cin>>x>>y;
        x--, y--;
        cout<<ans[x][y]<<"\n";
    }
    return 0;
}
