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
    int n, k;
    cin>>n>>k;
    vector<int>p(n);
    for(int i=0;i<n;i++) cin>>p[i], p[i]--;
    vector<vector<int>>v(n);
    set<pair<int, int>>s;
    int id = 0;
    vector<int>ans(n, -1);
    for(int i=0;i<n;i++){
        int j = p[i];
        auto it = s.lower_bound({j, 0});
        if(it == s.end()){
            if(k == 1){
                ans[j] = i + 1;
            }
            else{
                s.insert({j, id});
                v[id++].push_back(j);
            }
        }
        else{
            auto [_, cur] = *it;
            s.erase(it);
            v[cur].push_back(j);
            if(v[cur].size() == k){
                for(int x : v[cur]) ans[x] = i + 1;
                v[cur].clear();
            }
            else{
                s.insert({j, cur});
            }
        }
    }
    for(int i=0;i<n;i++) cout<<ans[i]<<"\n";

    return 0;
}
