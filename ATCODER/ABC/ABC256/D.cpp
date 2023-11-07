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
    vector<pair<int, int>>v(n);
    for(int i=0;i<n;i++){
        int l, r;
        cin>>l>>r;
        v[i] = {l, r};
    }
    sort(v.begin(), v.end());
    int L = -1, R = -1;
    vector<pair<int, int>>ans;
    for(auto [l, r] : v){
        if(l > R){
            if(R != -1) ans.push_back({L, R});
            L = l, R = r;
        }
        else R = max(R, r);
    }
    ans.push_back({L, R});
    for(auto [l, r] : ans) cout<<l<<" "<<r<<"\n";
    return 0;
}
