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

template <unsigned M_, unsigned G_, unsigned K_> struct FFT {
  static constexpr unsigned M = M_, M2 = 2U * M_, G = G_;
  static constexpr int K = K_;
  using num = modnum<M>;
  // 1, 1/4, 1/8, 3/8, 1/16, 5/16, 3/16, 7/16, ...
  num gs[1 << (K - 1)];
  constexpr FFT() : gs() {
    static_assert(K >= 2, "Fft: K >= 2 must hold");
    static_assert(!((M - 1) & ((1 << K) - 1)), "Fft: 2^K | M - 1 must hold");
    gs[0] = 1;
    gs[1 << (K - 2)] = num(G).pow((M - 1) >> K);
    for (int l = 1 << (K - 2); l >= 2; l >>= 1) {
      gs[l >> 1] = gs[l] * gs[l];
    }
    assert((gs[1] * gs[1]).x == M - 1);
    for (int l = 2; l <= 1 << (K - 2); l <<= 1) {
      for (int i = 1; i < l; ++i) {
        gs[l + i] = gs[l] * gs[i];
      }
    }
  }
  void fft(vector<num> &xs) const {
    const int n = int(xs.size());
    assert(!(n & (n - 1)) && n <= 1 << K);
    for (int l = n; l >>= 1; ) {
      for (int i = 0; i < (n >> 1) / l; ++i) {
        for (int j = (i << 1) * l; j < (i << 1 | 1) * l; ++j) {
          const num t = gs[i] * xs[j + l];
          xs[j + l] = xs[j] - t;
          xs[j] += t;
        }
      }
    }
  }
  void inverse_fft(vector<num> &xs) const {
    const int n = int(xs.size());
    assert(!(n & (n - 1)) && n <= 1 << K);
    for (int l = 1; l < n; l <<= 1) {
      reverse(xs.begin() + l, xs.begin() + (l << 1));
    }
    for (int l = 1; l < n; l <<= 1) {
      for (int i = 0; i < (n >> 1) / l; ++i) {
        for (int j = (i << 1) * l; j < (i << 1 | 1) * l; ++j) {
          const num t = gs[i] * (xs[j] - xs[j + l]);
          xs[j] += xs[j + l];
          xs[j + l] = t;
        }
      }
    }
    num invN = num(n).inv();
    for (int i = 0; i < n; ++i) xs[i] *= invN;
  }
  vector<num> convolve(vector<num> as, vector<num> bs) const {
    const int na = int(as.size()), nb = int(bs.size());
    int n = 1;
    for (; n < na + nb - 1; n <<= 1) {}
    as.resize(n); fft(as); 
    bs.resize(n); fft(bs);
    for (int i = 0; i < n; ++i) as[i] *= bs[i];
    inverse_fft(as); as.resize(na + nb - 1);
    return as;
  }
};

const FFT<998244353U, 3U, 23> fft;
using num = modnum<mod>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int>a(n), b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    reverse(b.begin(), b.end());
    vector<int>cnt(n);

    for(int k=0;k<5;k++){
        vector<num>c(n+n), d(n);
        for(int i=0;i<n;i++){
            c[i] = c[i+n] = (a[i]>>k&1);
            d[i] = (b[i]>>k&1);
        }
        auto res = fft.convolve(c, d);
        for(int i=n;i<n+n;i++){
            cnt[i-n] += int(res[i]) * (1<<k); 
        } 
    }
    int ans = 0;
    for(int i=0;i<n;i++) ans += a[i] + b[i];
    int mn = inf;
    for(int i=0;i<n;i++) mn = min(mn, cnt[i]);
    ans -= mn;

    cout<<ans<<"\n";


    return 0;
}
