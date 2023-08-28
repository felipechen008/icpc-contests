#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

lint power(lint x, lint y){
    x %= mod;
    lint res = 1;
    for(;y;y>>=1){
        if(y&1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    lint k, n, m;
    cin>>k>>n>>m;

    vector<lint>pot(50), pref(50);
    pot[0] = pref[0] = 1;
    for(int i=1;i<50;i++) pot[i] = pot[i-1] * k % mod;
    for(int i=1;i<50;i++) pref[i] = (pref[i-1] + pot[i]) % mod;
    
    lint aux = m;
    vector<pair<lint, int>>primes;
    for(lint i=2;i*i<=aux;i++){
        if(aux % i == 0){
            int cnt = 0;
            while(aux % i == 0) aux /= i, cnt++;
            primes.push_back({i, cnt});
        }
    }
    if(aux > 1){
        primes.push_back({aux, 1});
    }
    
    vector<lint>fac(50), ifac(50), c(50);
    fac[0] = 1;
    for(int i=1;i<50;i++) fac[i] = fac[i-1] * i % mod;
    ifac[49] = power(fac[49], mod - 2);
    for(int i=48;i>=0;i--) ifac[i] = ifac[i+1] * (i + 1) % mod;
    for(int i=1;i<50;i++) fac[i] = fac[i-1] * (k + i - 1) % mod; 
    for(int i=0;i<50;i++) c[i] = fac[i] * ifac[i] % mod;

    lint ans = 1;
    for(auto [p, cnt] : primes){
        lint d = 1;
        for(int i=0;i<cnt;i++) d *= p;
        lint phi = d / p * (p - 1);
        lint r = n % d;
        if(r){
            int l = 0;
            while(r % p == 0) r /= p, l++;
            lint last = n % d / r; 
            ans = ans * power(phi, k - 1) % mod * c[l] % mod;
        }
        else{
            lint last = phi;
            lint sum = 0;
            for(int i=0;i<cnt;i++){
                sum = (sum + c[i] * (last % mod)) % mod;
                last /= p;
            }
            lint cur = power(d, k) - power(phi, k - 1) * sum % mod;
            cur = (cur % mod + mod) % mod;
            ans = ans * cur % mod;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
