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
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a.begin(), a.end());
    vector<int>dp(n+1, -inf), mx(n+1);
    dp[0] = 0;
    for(int i=0;i<n;i++){
        if(a[i] <= i + 1) dp[i+1] = mx[i+1 - a[i]] + 1;
        mx[i+1] = max(mx[i], dp[i+1]);
    }
    for(int i=0;i<n;i++){
        if(a[i] > i + 1) dp[i+1] = n - a[i] + 1;
        else dp[i+1] = dp[i+1] + n - 1 - i;
    }

    vector<int>suf(n+1);
    for(int i=0;i<n;i++) suf[dp[i+1]] = max(suf[dp[i+1]], i+1);
    for(int i=n-1;i>=0;i--) suf[i] = max(suf[i], suf[i+1]);

    int q;
    cin>>q;
    while(q--){
        int k;
        cin>>k;
        cout<<suf[k]<<"\n";
    }
    return 0;
}
