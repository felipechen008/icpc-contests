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
    vector<lint>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    map<lint, int>dp;
    dp[0] = 0;
    lint pref = 0;
    int last = 0;
    for(int i=0;i<n;i++){
        pref += a[i];
        auto it = dp.upper_bound(pref);
        int cnt = last - 1;
        if(it != dp.begin()) cnt = max(cnt, prev(it)->nd);
        last = cnt;
        {
            it = dp.upper_bound(pref);
            if(it != dp.begin() && prev(it)->nd >= cnt) continue;
        }
        it = dp.lower_bound(pref);
        vector<lint>cur;
        while(it != dp.end() && it->nd <= cnt) cur.emplace_back(it->st), it++;
        for(lint u : cur) dp.erase(u);
        dp[pref] = cnt;
    }
    cout<<last + n<<"\n"; 

    return 0;
}
