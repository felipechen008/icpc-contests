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
    vector<pair<int, int>>os;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j] == 'o') os.push_back({i, j});
        }
    }
    auto [bx, by] = os[0];
    auto [ex, ey] = os[1];
    cout<<abs(ex - bx) + abs(ey - by)<<"\n";
    return 0;
}
