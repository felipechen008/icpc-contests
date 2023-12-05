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
    vector<vector<int>>v = {{6}, {3}, {1, 7}, {0, 4}, {2, 8}, {5}, {9}};
    string s;
    cin>>s;
    vector<int>cnt(7);
    for(int i=0;i<7;i++){
        for(int x : v[i]) cnt[i] += s[x] == '1';
    }
    bool ok = false;
    for(int i=0;i<7;i++){
        if(!cnt[i]) continue;
        for(int j=i+1;j<7;j++){
            if(cnt[j]) continue;
            for(int k=j+1;k<7;k++){
                if(cnt[k]) ok = true;
            }
        }
    }
    if(s[0] == '1') ok = false;
    if(ok) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}
