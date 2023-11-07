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
const int lim = 810;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<num>>choose(lim, vector<num>(lim));
    for(int i=0;i<lim;i++){
        choose[i][0] = choose[i][i] = 1;
        for(int j=1;j<i;j++) choose[i][j] = choose[i-1][j] + choose[i-1][j-1];
    }
    int n;
    cin>>n;
    vector<vector<pair<int, int>>>ind(n*n);
    vector<vector<int>>a(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cin>>a[i][j], a[i][j]--, ind[a[i][j]].emplace_back(i, j);
    }
    num ans = 0;
    for(int z=0;z<n*n;z++){
        if(ind[z].size() > n){
            // do DP
            vector<vector<num>>dp(n, vector<num>(n));
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++) if(a[i][j] == z) dp[i][j] += 1;
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(i+1 < n) dp[i+1][j] += dp[i][j];
                    if(j+1 < n) dp[i][j+1] += dp[i][j];
                    if(a[i][j] == z) ans += dp[i][j];
                }
            }
        }
        else{
            // do COMB
            int sz = (int)ind[z].size();
            for(int l=0;l<sz;l++){
                for(int r=0;r<sz;r++){
                    auto [c, d] = ind[z][l];
                    auto [e, f] = ind[z][r];
                    if(c <= e && d <= f){
                        ans += choose[e-c + f-d][e-c];
                    }
                }
            }
        }
    }
    cout<<ans<<"\n";


    return 0;
}
