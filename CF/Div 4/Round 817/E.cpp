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
    int t;
    cin>>t;
    while(t--){
        int n, q;
        cin>>n>>q;
        vector<vector<lint>>pref(1001, vector<lint>(1001));
        for(int i=0;i<n;i++){
            int h, w;
            cin>>h>>w;
            pref[h][w] += h * w;
        }
        for(int i=0;i<1000;i++){
            for(int j=0;j<1000;j++){
                pref[i+1][j+1] += pref[i+1][j] + pref[i][j+1] - pref[i][j];
            }
        }
        for(int i=0;i<q;i++){
            int h1, w1, h2, w2;
            cin>>h1>>w1>>h2>>w2;
            h2--, w2--;
            lint ans = pref[h2][w2] - pref[h1][w2] - pref[h2][w1] + pref[h1][w1];
            cout<<ans<<"\n";
        }
    }
    return 0;
}
