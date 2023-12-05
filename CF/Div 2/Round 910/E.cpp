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
        int n, m;
        cin>>n>>m;
        string s, t;
        cin>>s>>t;
        vector<vector<int>>ind(26);
        for(int i=0;i<n;i++) ind[s[i] - 'a'].push_back(i);
        vector<int>last(26, -1);
        bool ok = true;
        for(int i=0;i<m;i++){
            int c = t[i] - 'a';
            int x = -1;
            for(int j=c;j<26;j++) x = max(x, last[j]);
            int id = int(upper_bound(ind[c].begin(), ind[c].end(), x) - ind[c].begin());
            if(id == (int)ind[c].size()){
                ok = false;
                break;
            }
            else{
                last[c] = ind[c][id];
            }
        }
        if(ok) cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}
