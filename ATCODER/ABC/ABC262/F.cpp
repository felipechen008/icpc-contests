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
    vector<int>a(n), pos(n);
    for(int i=0;i<n;i++) cin>>a[i], a[i]--, pos[a[i]] = i;
    vector<int>mn(k + 2);
    mn[0] = n;
    for(int i=0;i<=k;i++) mn[i+1] = min(mn[i], a[i]);
    int ans = 0;
    int cur = mn[k + 1];
    int test = 0;
    vector<int>res;
    for(int i=1;i<=k;i++){
        if(a[n - i] < cur){
            ans = i;
            cur = a[n - i];
            res.push_back(a[n - i]);
        }
        else if(!a[n - i]){
            test = i;
        }
    }
    reverse(res.begin(), res.end());
    auto f = [&](int cnt)->vector<int> {
        vector<int>v;
        int x = k - cnt;
        set<int>s;
        for(int i=0;i<=k-cnt;i++){
            s.insert(a[i]);
        }
        int l = 0, r = k - cnt + 1;
        while(x && l < r){
            int u = (*s.begin());
            int ind = pos[u];
            x -= ind - l;
            for(int i=l;i<=ind;i++) s.erase(a[i]);
            v.push_back(u);
            l = ind + 1;
            if(r < n - cnt) s.insert(a[r++]);
        }
        for(int i=l;i<n-cnt;i++) v.push_back(a[i]);
        while(x) v.pop_back(), x--;
        return v;
    };
    auto v = f(ans);
    if(test){
        cur = mn[k - test + 1];
        for(int i=1;i<=test;i++){
            if(a[n-i] < cur){
                cur = a[n - i];
                res.push_back(a[n - i]);
            }
        }
        reverse(res.begin(), res.end());
        auto w = f(test);
        for(int u : w) res.push_back(u);
        if(v < res) swap(v, res);
    }
    else{
        for(int u : v) res.push_back(u);
    }
    for(int u : res) cout<<u+1<<" ";
    cout<<"\n";

    return 0;
}
