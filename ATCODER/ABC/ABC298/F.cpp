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
    vector<int>r(n), c(n), x(n);
    map<int, lint>sumr, sumc;
    map<int, set<int>>sr;
    for(int i=0;i<n;i++){
        cin>>r[i]>>c[i]>>x[i];
        sumr[r[i]] += x[i];
        sumc[c[i]] += x[i];
        sr[r[i]].insert(c[i]);
    }
    lint ans = 0;
    for(int i=0;i<n;i++){
        ans = max(ans, sumr[r[i]] + sumc[c[i]] - x[i]);
    }
    map<lint, int>rest;
    for(auto p : sumc) rest[p.nd]++;
    for(auto& p : sr){
        auto z = sumr[p.st];
        for(int u : p.nd){
            rest[sumc[u]]--;
            if(!rest[sumc[u]]) rest.erase(sumc[u]);
        }
        ans = max(ans, z + (rest.empty() ? 0 : rest.rbegin()->st));
        for(int u : p.nd){
            rest[sumc[u]]++;
        }
    }

    cout<<ans<<"\n";
    return 0;
}
