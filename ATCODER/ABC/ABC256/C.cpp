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
    vector<int>r(3), col(3);
    for(int i=0;i<3;i++) cin>>r[i];
    for(int i=0;i<3;i++) cin>>col[i];
    int ans = 0;
    for(int a=1;a<=30;a++){
        for(int b=1;b<=30;b++){
            for(int d=1;d<=30;d++){
                for(int e=1;e<=30;e++){
                    int c = (r[0] - a - b);
                    int f = (r[1] - d - e);
                    int g = (col[0] - a - d);
                    int h = (col[1] - b - e);
                    int i = (r[2] - g - h);
                    if(c > 0 && f > 0 && g > 0 && h > 0 
                    && i > 0 && i == col[2] - c - f) ans++;
                }
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
