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
    vector dp(300, vector<int>(300));
    for(int i=0;i<300;i++){
        for(int j=0;j<300;j++){
            if(abs(i - j) <= 1) continue;
            vector<bool>c(601);
            for(int k=0;k<i;k++) c[dp[k][j]] = 1;
            for(int k=0;k<j;k++) c[dp[i][k]] = 1;
            for(int k=0;k<=600;k++){
                if(!c[k]){
                    dp[i][j] = k;
                    break;
                }
            }
        }
    }

    auto get = [&](int x1, int y1, int x2, int y2)->int {
        int cnt = dp[x1][x2] ^ dp[y1][y2];
        if(abs(x1 - x2) == 1 && abs(y1 - y2) == 1) return 0;
        return cnt == 0;
    };

    int q;
    cin>>q;
    for(int z=0;z<q;z++){
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        x1--, y1--, x2--, y2--;
        if(tie(x1, y1) > tie(x2, y2)){
            swap(x1, x2);
            swap(y1, y2);
        }
        int ans = 0;
        for(int i=0;i<x1;i++) ans += get(i, y1, x2, y2);
        for(int i=0;i<y1;i++) ans += get(x1, i, x2, y2);

        if(x1 == x2) for(int i=y1+1;i<y2;i++) ans += get(x1, y1, x2, i);
        else for(int i=0;i<y2;i++) ans += get(x1, y1, x2, i);

        if(y1 == y2) for(int i=x1+1;i<x2;i++) ans += get(x1, y1, i, y2);
        else for(int i=0;i<x2;i++) ans += get(x1, y1, i, y2);
        cout<<ans<<"\n";
    }


    return 0;
}
