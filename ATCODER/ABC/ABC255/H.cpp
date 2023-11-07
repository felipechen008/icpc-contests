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
num i2 = num(2).inv();

num get(num l, num r){
    return ( r * (r + 1) - (l - 1) * l ) * i2;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    lint n, q;
    cin>>n>>q;
    set<array<lint, 3>>s;
    s.insert({n, 1, 0});
    for(int i=0;i<q;i++){
        lint d, l, r;
        cin>>d>>l>>r;
        num ans = num(d) * get(l, r);
        auto it = s.lower_bound({r, 0, 0});
        while( (*it)[1] > l){
            auto [y, x, z] = *it;
            ans -= num(z) * get(x, min(y, r));
            it--;
            s.erase(next(it));
            if(y > r){
                s.insert({y, r + 1, z});
            }
        }
        auto [y, x, z] = *it;
        ans -= num(z) * get(max(l, x), min(r, y));
        s.erase(it);
        if(l > x) s.insert({l-1, x, z});
        if(y > r) s.insert({y, r + 1, z});
        s.insert({r, l, d});
        cout<<ans<<"\n";
    }
    return 0;
}
