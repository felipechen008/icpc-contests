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
    vector<lint>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<lint>v = a;
    vector<pair<lint, lint>>e(m);
    for(int i=0;i<m;i++){
        lint x, y;
        cin>>x>>y;
        v.push_back(x);
        v.push_back(x - y);
        e[i] = {x, x-y};
    }   
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int sz = int(v.size());
    vector<vector<int>>g(sz);
    map<lint, int>f;
    for(auto& [x, y] : e){
        x = int(lower_bound(v.begin(), v.end(), x) - v.begin());
        y = int(lower_bound(v.begin(), v.end(), y) - v.begin());
        g[x].push_back(y);
    }
    vector<lint>nim(sz);
    int cnt = 0;

    for(int x=0;x<sz;x++){
        map<lint, int>f2;
        for(int y : g[x]){
            f2[nim[y]]++;
        }
        bool equal = true;
        for(auto [p, q] : f2){
            if(f.count(p)){
                if(f[p] < q){
                    equal = false;
                    nim[x] = p;
                    break;
                }
            }
            else{
                equal = false;
                nim[x] = p;
                break;
            }
        }
        if(equal){
            nim[x] = v[x] - cnt;
        }
        else{
            cnt++;
            f[nim[x]]++;
        }
    }
    lint ans = 0;
    for(auto& u : a){
        u = int(lower_bound(v.begin(), v.end(), u) - v.begin());
        ans ^= nim[u];
    }
    if(ans) cout<<"Takahashi\n";
    else cout<<"Aoki\n";

    return 0;
}
