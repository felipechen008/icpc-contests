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
num choose[500][500];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<500;i++){
        choose[i][0] = choose[i][i] = 1;
        for(int j=1;j<i;j++) choose[i][j] = choose[i-1][j] + choose[i-1][j-1]; 
    }

    int n, m;
    cin>>n>>m;
    int sz = (n / 2) * ( (n + 1) / 2 );
    vector<num>cnt(sz + 1);
    for(int k=1;k<=sz;k++){
        for(int i=0;i<=k;i++){
            if( (k-i)&1 ) cnt[k] -= choose[k][i] * num(i).pow(m); 
            else cnt[k] += choose[k][i] * num(i).pow(m);
        }
    }
    vector<vector<num>>tot(n+1, vector<num>(sz + 1));
    for(int x=1;x<=n;x++){
        int cursz = (x / 2) * ((x + 1) / 2);
        for(int y=0;y<=cursz;y++){
            for(int i=0;i<= x;i++){
                tot[x][y] += choose[x][i] * choose[i * (x - i)][y];
            }
        }
    }
    auto dp = tot;
    for(int x=1;x<=n;x++){
        int cursz = (x / 2) * ((x + 1) / 2);
        for(int y=0;y<=cursz;y++){
            for(int i=1;i<x;i++){
                for(int j=0;j<=y;j++){
                    dp[x][y] -= choose[x-1][i-1] * dp[i][j] * tot[x-i][y-j];
                }
            }
        }
    }
    num i2 = num(2).inv();
    for(int x=1;x<=n;x++){
        int cursz = (x / 2) * ((x + 1) / 2);
        for(int y=0;y<=cursz;y++){
            dp[x][y] *= i2;
        }
    }
    auto res = dp;
    for(int x=1;x<=n;x++){
        int cursz = (x / 2) * ((x + 1) / 2);
        for(int y=0;y<=cursz;y++){
            for(int i=1;i<x;i++){
                for(int j=0;j<=y;j++){
                    res[x][y] += choose[x-1][i-1] * dp[i][j] * res[x-i][y-j];
                }
            }
        }
    }
    num ans = 0;
    for(int k=1;k<=sz;k++) ans += res[n][k] * cnt[k];
    ans *= num(2).pow(m);
    cout<<ans.x<<"\n";

    return 0;
}
