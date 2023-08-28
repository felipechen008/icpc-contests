#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int ms = 1e6 + 10;

lint power(lint x, lint y){
    lint res = 1;
    x %= mod;
    for(;y;y >>= 1){
        if(y&1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<int>lp(ms);
    vector<int>primes;
    primes.reserve(ms);
    for(int i=2;i<ms;i++){
        if(!lp[i]){
            lp[i] = i;
            primes.push_back(i);
        }
        for(int p : primes){
            if(p > ms/i) break;
            lp[p * i] = p; 
            if(i % p == 0) break;
        }
    }
    vector<lint>fac(3002), ifac(3002); 
    fac[0] = 1;
    for(int i=1;i<3002;i++) fac[i] = fac[i-1] * i % mod;
    ifac[3001] = power(fac[3001], mod-2);
    for(int i=3000;i>=0;i--) ifac[i] = ifac[i+1] * (i + 1) % mod;

    int n;
    cin>>n;
    vector<int>a(n+n), cnt(ms);
    for(int i=0;i<n+n;i++) cin>>a[i], cnt[a[i]]++;
    sort(a.begin(), a.end());
    vector dp(n+n+1, vector<lint>(n+1));
    dp[0][0] = 1;
    for(int i=0;i<n+n;i++){
        for(int j=0;j<=n;j++){
            dp[i+1][j] += dp[i][j];
            dp[i+1][j] %= mod;
            if(j < n && lp[a[i]] == a[i] && (i == n+n-1 || a[i] != a[i+1])){
                dp[i+1][j+1] += dp[i][j]  * cnt[a[i]]% mod;
                dp[i+1][j+1] %= mod;
            }
        }
    }
    lint cur = fac[n];
    for(int i=0;i<ms;i++) cur = cur * ifac[cnt[i]] % mod;
    lint ans = dp[n+n][n] * cur % mod;
    cout<<ans<<"\n";
    return 0;
}
