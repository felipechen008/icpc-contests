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
    static constexpr unsigned M = M_;
    using ll = int64_t; using ull = uint64_t; unsigned x;
    modnum& norm(unsigned a) { x = a < M ? a : a - M; return *this; }
    constexpr modnum(ll a = 0U) : x(unsigned((a %= ll(M)) < 0 ? a + ll(M) : a)) {}
    explicit operator int() const { return x; }
    modnum& operator+=(const modnum& a) { return norm(x + a.x); }
    modnum& operator-=(const modnum& a) { return norm(x - a.x + M); }
    modnum& operator*=(const modnum& a) { x = unsigned(ull(x) * a.x % M); return *this; }
    modnum& operator/=(const modnum& a) { return (*this *= a.inv()); }
    modnum operator+(const modnum& a) const { return (modnum(*this) += a); }
    modnum operator-(const modnum& a) const { return (modnum(*this) -= a); }
    modnum operator*(const modnum& a) const { return (modnum(*this) *= a); }
    modnum operator/(const modnum& a) const { return (modnum(*this) /= a); }
    template<typename T> friend modnum operator+(T a, const modnum& b) { return (modnum(a) += b); }
    template<typename T> friend modnum operator-(T a, const modnum& b) { return (modnum(a) -= b); }
    template<typename T> friend modnum operator*(T a, const modnum& b) { return (modnum(a) *= b); }
    template<typename T> friend modnum operator/(T a, const modnum& b) { return (modnum(a) /= b); }
    modnum operator+() const { return *this; }
    modnum operator-() const { return modnum() - *this; }
    modnum pow(ll e) const {
        if (e < 0) return inv().pow(-e);
        modnum b = x, xe = 1U;
        for (; e; e >>= 1) { if (e & 1) xe *= b; b *= b; }
        return xe;
    }
    modnum inv() const { return minv(x, M); }
    friend modnum inv(const modnum& a) { return a.inv(); }
    explicit operator bool() const { return x; }
    friend bool operator==(const modnum& a, const modnum& b) { return a.x == b.x; }
    friend bool operator!=(const modnum& a, const modnum& b) { return a.x != b.x; }
    friend ostream &operator<<(ostream& os, const modnum& a) { return os << a.x; }
    friend istream &operator>>(istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
};

using num = modnum<mod>;
const int bucket = 440;
const num i2 = num(2).inv();

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin>>n>>q;
    vector<num>a(n), d(n);
    for(int i=0;i<n;i++) cin>>a[i];
    {
        d = a;
        for(int j=0;j<3;j++){
            for(int i=1;i<n;i++) d[i] += d[i-1];
        }
    }
    vector<num>aux(n);
    vector<bool>w(n);
    vector<int>cur;
    while(q--){
        int op, x;
        cin>>op>>x;
        x--;
        if(op == 1){
            num v;
            cin>>v;
            aux[x] = v;            
            if(!w[x]) w[x] = 1, cur.push_back(x);
        }
        else{
            num ans = d[x];
            for(int i : cur){
                if(i > x) continue;
                ans += (aux[i] - a[i]) * (x-i+1) * (x-i+2) * i2;
            }
            cout<<ans<<"\n";
        }
        if( (int)cur.size() == bucket){
            for(int i : cur) a[i] = aux[i];
            d = a;
            for(int j=0;j<3;j++){
                for(int i=1;i<n;i++) d[i] += d[i-1];
            }
            for(int i : cur) aux[i] = 0, w[i] = 0;
            cur.clear();
        }
    }

    return 0;
}
