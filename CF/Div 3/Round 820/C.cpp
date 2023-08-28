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
        string s;
        cin>>s;
        int n = int(size(s));
        int d = s[0] - 'a', e = s.back() - 'a';
        int ans = abs(d - e);
        vector<vector<int>>ind(26);
        for(int i=0;i<n;i++) ind[s[i] - 'a'].push_back(i);
        vector<int>ids;
        if(d > e){
            for(int i=d;i>=e;i--){
                for(int j : ind[i]) ids.push_back(j);
            }
        }
        else{
            for(int i=d;i<=e;i++){
                for(int j : ind[i]) ids.push_back(j);
            }
        }
        cout<<ans<<" "<<size(ids)<<"\n";
        for(int j : ids) cout<<j+1<<" ";
        cout<<"\n";
    }
    return 0;
}
