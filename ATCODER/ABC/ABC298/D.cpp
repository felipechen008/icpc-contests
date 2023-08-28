#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<unsigned M_> struct modnum {
    static constexpr unsigned M = M_;
    using ll = long long; using ull = unsigned long long; unsigned x;

    // ec131c
    constexpr modnum() : x(0U) {}
    constexpr modnum(unsigned a) : x(a % M) {}
    constexpr modnum(ull a) : x(a % M) {}
    constexpr modnum(int a) : x(((a %= static_cast<int>(M)) < 0) ? (a + static_cast<int>(M)) : a) {}
    constexpr modnum(ll a) : x(((a %= static_cast<ll>(M)) < 0) ? (a + static_cast<ll>(M)) : a) {}
    // da738b
    explicit operator int() const { return x; }
    modnum& operator+=(const modnum& a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
    modnum& operator-=(const modnum& a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
    modnum& operator*=(const modnum& a) { x = unsigned((static_cast<ull>(x) * a.x) % M); return *this; }
    modnum& operator/=(const modnum& a) { return (*this *= a.inv()); }
    // ef603f
    modnum operator+(const modnum& a) const { return (modnum(*this) += a); }
    modnum operator-(const modnum& a) const { return (modnum(*this) -= a); }
    modnum operator*(const modnum& a) const { return (modnum(*this) *= a); }
    modnum operator/(const modnum& a) const { return (modnum(*this) /= a); }
    modnum operator+() const { return *this; }
    modnum operator-() const { modnum a; a.x = x ? (M - x) : 0U; return a; }
    // b8b96c
    template<typename T> friend modnum operator+(T a, const modnum& b) { return (modnum(a) += b); }
    template<typename T> friend modnum operator-(T a, const modnum& b) { return (modnum(a) -= b); }
    template<typename T> friend modnum operator*(T a, const modnum& b) { return (modnum(a) *= b); }
    template<typename T> friend modnum operator/(T a, const modnum& b) { return (modnum(a) /= b); }

    modnum pow(ll e) const {
        if (e < 0) return inv().pow(-e);
        modnum x2 = x, xe = 1U;
        for (; e; e >>= 1) {
            if (e & 1) xe *= x2;
            x2 *= x2;
        }
        return xe;
    }
    modnum inv() const {
        unsigned a = x, b = M; int y = 1, z = 0;
        while (a) {
            const unsigned q = (b/a), c = (b - q*a); 
            b = a, a = c; const int w = z - static_cast<int>(q) * y;
            z = y, y = w;
        } assert(b == 1U); return modnum(z);
    }
    friend modnum inv(const modnum& a) { return a.inv(); }

    explicit operator bool() const { return x; }
    friend bool operator==(const modnum& a, const modnum& b) { return a.x == b.x; }
    friend bool operator!=(const modnum& a, const modnum& b) { return a.x != b.x; }
    friend ostream &operator<<(ostream& os, const modnum& a) { return os << a.x; }
    friend istream &operator>>(istream& in, modnum& n) { ull v_; in >> v_; n = modnum(v_); return in; }
};

using num = modnum<mod>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<num>p(600100);
    p[0] = 1;
    for(int i=1;i<600100;i++) p[i] = p[i-1] * 10;
    vector<int>v;
    v.reserve(600100);
    v.push_back(1);

    int q;
    cin>>q;
    num ans = 1;

    int ind = 0;
    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int x;
            cin>>x;
            ans = ans * 10 + x;
            v.push_back(x);
        }
        else if(op == 2){
            ans -= p[int(size(v)) - ind - 1] * v[ind];
            ind++;
        }
        else cout<<ans<<"\n";
    }

    return 0;
}
