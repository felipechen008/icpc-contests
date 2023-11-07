#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template <typename T> struct Matrix : vector<vector<T>> {
    using vector<vector<T>>::vector;
    using vector<vector<T>>::size;
    int h() const { return int(size()); }
    int w() const { return int((*this)[0].size()); }
    Matrix operator*(const Matrix& r) const {
        assert(w() == r.h());
        Matrix res(h(), vector<T>(r.w()));
        for (int i = 0; i < h(); ++i) {
            for (int j = 0; j < r.w(); ++j) {
                for (int k = 0; k < w(); ++k) {
                    res[i][j] += (*this)[i][k] * r[k][j];
                }
            }
        }
        return res;
    }
    friend vector<T> operator*(const Matrix<T>& A, const vector<T>& b) {
        int N = int(A.size()), M = int(A[0].size());
        vector<T> y(N);
        for (int i = 0; i < N; ++i) 
            for (int j = 0; j < M; ++j) y[i] += A[i][j] * b[j];
        return y;
    }
    Matrix& operator*=(const Matrix& r) { return *this = *this * r; }
    Matrix pow(lint n) const {
        assert(h() == w());
        Matrix x = *this, r(h(), vector<T>(w()));
        for (int i = 0; i < h(); ++i) r[i][i] = T(1);
        while (n) { if (n & 1) r *= x; x *= x; n >>= 1; }
        return r;
    }
};

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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    lint n, d;
    cin>>n>>d;
    d++;
    vector<num>fac(d+1), ifac(d+1);
    {
        fac[0] = 1;
        for(int i=1;i<=d;i++) fac[i] = fac[i-1] * i;
        ifac[d] = fac[d].inv();
        for(int i=d-1;i>=0;i--) ifac[i] = ifac[i+1] * (i + 1);
    }
    auto choose = [&](int x, int y)->num {
        if(x < 0 || y < 0 || x < y) return 0;
        return fac[x] * ifac[y] * ifac[x-y];
    };
    num ans = 2;
    for(int k=1;k<d;k++){
        Matrix<num>A = {{choose(d-2, k-2), choose(d-2, k-1)}, 
                        {choose(d-2, k-1), choose(d-2, k)}};
        Matrix<num>B = {{choose(d-2, k-2)}, {choose(d-2, k-1)}};
        Matrix<num>C = {{choose(d-2, k-1)}, {choose(d-2, k)}};
        A = A.pow(n-1);
        auto res = A * B;
        ans += res[0][0];
        res = A * C;
        ans += res[1][0];
    }
    cout<<ans<<"\n";




    return 0;
}
