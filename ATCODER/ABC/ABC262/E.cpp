#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int minv(int a, int m) {
    a %= m; assert(a);
    return a == 1 ? 1 : int(m - int64_t(minv(m, a)) * m / a);
}
template<unsigned M_> struct modnum {
    static constexpr unsigned M = M_; using num = modnum;
    using ll = int64_t; using ull = uint64_t; unsigned x;
    num& norm(unsigned a){x = a<M ? a : a-M;return *this;}
    constexpr modnum(ll a = 0U) : x(unsigned((a %= ll(M)) < 0 ? a + ll(M) : a)) {}
    explicit operator int() const { return x; }
    num& operator+=(const num& a){ return norm(x+a.x); }
    num& operator-=(const num& a){ return norm(x-a.x+M); }
    num& operator*=(const num& a){ x = unsigned(ull(x)*a.x%M); return *this; }
    num& operator/=(const num& a){ return (*this *= a.inv());}
    num operator+(const num& a) const {return (num(*this) += a);}
    num operator-(const num& a) const {return (num(*this) -= a);}
    num operator*(const num& a) const {return (num(*this) *= a);}
    num operator/(const num& a) const {return (num(*this) /= a);}
    template<typename T> friend num operator+(T a, const num& b){ return (num(a) += b); }
    template<typename T> friend num operator-(T a, const num& b){ return (num(a) -= b); }
    template<typename T> friend num operator*(T a, const num& b){ return (num(a) *= b); }
    template<typename T> friend num operator/(T a, const num& b){ return (num(a) /= b); }
    num operator+() const { return *this; }
    num operator-() const { return num() - *this; }
    num pow(ll e) const {
        if (e < 0) { return inv().pow(-e); } num b = x, xe = 1U;
        for (; e; e >>= 1) { if (e & 1) xe *= b; b *= b; }
        return xe;
    }
    num inv() const { return minv(x, M); }
    friend num inv(const num& a) { return a.inv(); }
    explicit operator bool() const { return x; }
    friend bool operator==(const num& a, const num& b){return a.x == b.x;}
    friend bool operator!=(const num& a, const num& b){return a.x != b.x;}
};

using num = modnum<mod>;
const int lim = 1<<19;
num fac[lim], ifac[lim];

void prep(){
    fac[0] = 1;
    for(int i=1;i<lim;i++) fac[i] = fac[i-1] * i;
    ifac[lim - 1] = fac[lim - 1].inv();
    for(int i=lim-2;i>=0;i--) ifac[i] = ifac[i+1] * (i + 1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    prep();
    int n, m, k;
    cin>>n>>m>>k;
    vector<int>d(n);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        d[a]++;
        d[b]++;
    }
    int x = 0;
    for(int i=0;i<n;i++) x += d[i]&1;
    int y = n - x;
    num ans = 0;
    for(int i=0;i<=min(x, k);i+=2){
        if(y < k - i) continue;
        ans += fac[x] * ifac[i] * ifac[x-i] *
                fac[y] * ifac[k-i] * ifac[y-k+i];
    }
    cout<<ans.x<<"\n";
    return 0;
}
