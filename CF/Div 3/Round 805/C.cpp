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
        map<int, vector<int>>f;
        int n, q;
        cin>>n>>q;
        vector<int>v(n);
        for(int i=0;i<n;i++) cin>>v[i], f[v[i]].push_back(i);
        for(int i=0;i<q;i++){
            int a, b;
            cin>>a>>b;
            auto &va = f[a], &vb = f[b];
            if(va.empty() || lower_bound(vb.begin(), vb.end(), va[0]) == vb.end()) cout<<"NO\n";
            else cout<<"YES\n";
        }
    }
    return 0;
}
