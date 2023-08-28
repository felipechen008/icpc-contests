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
    int k;
    cin>>k;
    int b = -1;
    for(int i=0;i<14;i++){
        if((1<<i) >= k){
            b = i;
            break;
        }
    }

    if(!b){
        cout<<0<<"\n";
        return 0;
    }

    int left = (b + 1) / 2, right = b / 2;
    vector<vector<int>>val(100, vector<int>(100));
    k--;
    int cnt = 0;
    int tot = (1<<b) - 1;
    for(int i=0;i<1<<left;i++){
        for(int j=0;j<1<<right;j++){
            if(cnt == k){
                val[i][j] = tot;
            }
            else{
                val[i][j] = i ^ (j << left);
                cnt++;
            }
        }
    }
    for(int i=0;i<1<<left;i++) val[i][1<<right] = tot;
    for(int j=0;j<1<<right;j++) val[1<<left][j] = tot;
    val[1<<left][1<<right] = tot;

    cout<<b<<"\n";
    for(int x=0;x<b;x++){
        vector<pair<int, int>>ans;
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                if(val[i][j]>>x&1) ans.emplace_back(i+1, j+1);
            }
        }
        cout<<size(ans)<<" ";
        for(auto [c, d] : ans) cout<<c<<" "<<d<<" ";
        cout<<"\n";
    }


    return 0;
}
