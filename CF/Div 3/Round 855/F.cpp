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
    vector<string>s(n);
    vector<vector<int>>f(n, vector<int>(26));
    for(int i=0;i<n;i++){
        cin>>s[i];
        for(char c : s[i]) f[i][c - 'a']++;
    }
    vector<int>cnt(1<<26);
    lint ans = 0;
    vector<int>mask(n);
    for(int i=0;i<n;i++){
        for(int d=0;d<26;d++) if(f[i][d]&1) mask[i] |= 1<<d;
    }
    for(int d=0;d<26;d++){
        int tot = (1<<26) - 1;
        tot ^= (1<<d);
        for(int i=0;i<n;i++){
            if(f[i][d]) continue;
            ans += cnt[tot ^ mask[i]];
            cnt[mask[i]]++;
        }
        for(int i=0;i<n;i++){
            if(f[i][d]) continue;
            cnt[mask[i]]--;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
