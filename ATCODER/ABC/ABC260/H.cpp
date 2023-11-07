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

inline int nxt_pow2(int s) { return 1 << (s > 1 ? 32 - __builtin_clz(s-1) : 0); }
template <typename T> struct root_of_unity {};
constexpr unsigned primitive_root(unsigned M) {
    if (M == 880803841U) return 26U; // (M2)
    else if (M == 943718401U) return 7U; // (M4)
    else if (M == 918552577U) return 5U; // (M6)
    else return 3U;
}
template<unsigned MOD> struct root_of_unity<modnum<MOD>> {
    static constexpr modnum<MOD> g0 = primitive_root(MOD);
    static modnum<MOD> f(int K) {
        assert((MOD-1)%K == 0); return g0.pow((MOD-1)/K);
    }
};
template<typename T> struct FFT {
    vector<T> rt; vector<int> rev;
    FFT() : rt(2, T(1)) {}
    void init(int N) {
        N = nxt_pow2(N);
        if (N > int(rt.size())) {
            rev.resize(N); rt.reserve(N);
            for (int a = 0; a < N; ++a)
                rev[a] = (rev[a/2] | ((a&1)*N)) >> 1;
            for (int k = int(rt.size()); k < N; k *= 2) {
                rt.resize(2*k);
                T z = root_of_unity<T>::f(2*k);
                for (int a = k/2; a < k; ++a)
                    rt[2*a] = rt[a], rt[2*a+1] = rt[a] * z;
            }
        }
    }
    void fft(vector<T>& xs, bool inverse) const {
        int N = int(xs.size());
        int s = __builtin_ctz(int(rev.size())/N);
        if (inverse) reverse(xs.begin() + 1, xs.end());
        for (int a = 0; a < N; ++a) {
            if (a < (rev[a] >> s)) swap(xs[a], xs[rev[a] >> s]);
        }
        for (int k = 1; k < N; k *= 2) {
            for (int a = 0; a < N; a += 2*k) {
                int u = a, v = u + k;
                for (int b = 0; b < k; ++b, ++u, ++v) {
                    T z = rt[b + k] * xs[v];
                    xs[v] = xs[u] - z, xs[u] = xs[u] + z;
                }
            }
        }
        if (inverse) 
            for (int a = 0; a < N; ++a) xs[a] = xs[a] * inv(T(N));
    }
    vector<T> convolve(vector<T> as, vector<T> bs) {
        int N = int(as.size()), M = int(bs.size());
        int K = N + M - 1, S = nxt_pow2(K);
        if (min(N, M) <= 64) {
            vector<T> res(K);
            for (int u = 0; u < N; ++u) for (int v = 0; v < M; ++v)
                res[u + v] = res[u + v] + as[u] * bs[v];
            return res;
        } else {
            as.resize(S), bs.resize(S);
            fft(as, false); fft(bs, false);
            for (int i = 0; i < S; ++i) as[i] = as[i] * bs[i];
            fft(as, true); as.resize(K); return as;
        }
    }
};
using num = modnum<998244353U>;
FFT<num>fft_data;
const int lim = 1<<20;
num fact[lim], ifact[lim], invs[lim];

template<unsigned M> struct Poly : public vector<modnum<M>> {
    Poly() {}
    explicit Poly(int n) : vector<modnum<M>>(n) {}
    Poly(const vector<modnum<M>> &vec) : vector<modnum<M>>(vec) {}
    Poly(std::initializer_list<modnum<M>> il) : vector<modnum<M>>(il) {}
    int size() const { return vector<modnum<M>>::size(); }
    num at(long long k) const { return (0 <= k && k < size()) ? (*this)[k] : 0U; }
    int ord() const { for (int i = 0; i < size(); ++i) if (int((*this)[i])) return i; return -1; }
    int deg() const { for (int i = size(); --i >= 0;) if (int((*this)[i])) return i; return -1; }
    Poly mod(int n) const { return Poly(vector<modnum<M>>(this->data(), this->data() + min(n, size()))); }
    friend std::ostream &operator<<(std::ostream &os, const Poly &fs) {
        os << "[";
        for (int i = 0; i < fs.size(); ++i) { if (i > 0) os << ", "; os << fs[i]; }
        return os << "]";
    }
    Poly &operator+=(const Poly &fs) { // d36be
        if (size() < fs.size()) this->resize(fs.size());
        for (int i = 0; i < fs.size(); ++i) (*this)[i] += fs[i];
        return *this;
    }
    Poly &operator-=(const Poly &fs) { // 1f585
        if (size() < fs.size()) this->resize(fs.size());
        for (int i = 0; i < fs.size(); ++i) (*this)[i] -= fs[i];
        return *this;
    }
    Poly &operator*=(const Poly &fs) { // 24a99
        if (this->empty() || fs.empty()) return *this = {};
        *this = fft_data.convolve(*this, fs);
        return *this;
    }
    Poly &operator*=(const num &a) { // ea9fb
        for (int i = 0; i < size(); ++i) (*this)[i] *= a;
        return *this;
    }
    Poly &operator/=(const num &a) { // 71618
        const num b = a.inv();
        for (int i = 0; i < size(); ++i) (*this)[i] *= b;
        return *this;
    }
    Poly &operator/=(const Poly &fs) { // 291cd
        auto ps = fs;
        if (size() < ps.size()) return *this = {};
        int s = int(size()) - int(ps.size()) + 1;
        int nn = 1; for (; nn < s; nn <<= 1) {}
        reverse(this->begin(), this->end());
        reverse(ps.begin(), ps.end());
        this->resize(nn); ps.resize(nn);
        ps = ps.inv();
        *this = *this * ps;
        this->resize(s); reverse(this->begin(), this->end());
        return *this;
    }
    Poly &operator%=(const Poly& fs) { // d6a38
        if (size() >= fs.size()) {
            Poly Q = (*this / fs) * fs;
            this->resize(fs.size() - 1);
            for (int x = 0; x < int(size()); ++x) (*this)[x] -= Q[x];
        }
        while (size() && this->back() == 0) this->pop_back();
        return *this;
    }
    Poly inv() const { // c47df7
        if (this->empty()) return {};
        Poly b({(*this)[0].inv()}), fs;
        b.reserve(2 * int(this->size()));
        while (b.size() < this->size()) {
            int len = 2 * int(b.size());
            b.resize(2 * len, 0);
            if (int(fs.size()) < 2 * len) fs.resize(2 * len, 0);
            fill(fs.begin(), fs.begin() + 2 * len, 0);
            copy(this->begin(), this->begin() + min(len, int(this->size())), fs.begin());
            fft_data.fft(b, false);
            fft_data.fft(fs, false);
            for (int x = 0; x < 2*len; ++x) b[x] = b[x] * (2 - fs[x] * b[x]);
            fft_data.fft(b, true);
            b.resize(len);
        }
        b.resize(this->size()); return b;
    }
    Poly differential() const { // 0b718
        if (this->empty()) return {};
        Poly f(max(size() - 1, 1));
        for (int x = 1; x < size(); ++x) f[x - 1] = x * (*this)[x];
        return f;
    }
    Poly integral() const { // 71d33
        if (this->empty()) return {};
        Poly f(size() + 1);
        for (int x = 0; x < size(); ++x) f[x + 1] = invs[x + 1] * (*this)[x];
        return f;
    }
    Poly log() const { // 6a365
        if (this->empty()) return {};
        Poly f = (differential() * inv()).integral();
        f.resize(size()); return f;
    }
    Poly exp() const { // 25174b
        Poly f = {1};
        if (this->empty()) return f;
        while (f.size() < size()) {
            int len = min(f.size() * 2, size());
            f.resize(len);
            Poly d(len);
            copy(this->begin(), this->begin() + len, d.begin());
            Poly g = d - f.log();
            g[0] += 1;
            f *= g;
            f.resize(len);
        }
        return f;
    }
    Poly pow(int N) const { // 48fee9
        Poly b(size());
        if (N == 0) { b[0] = 1; return b; }
        int p = 0;
        while (p < size() && (*this)[p] == 0) ++p;
        if (1LL * N * p >= size()) return b;
        num mu = ((*this)[p]).pow(N), di = ((*this)[p]).inv();
        Poly c(size() - N*p);
        for (int x = 0; x < int(c.size()); ++x) {
            c[x] = (*this)[x + p] * di;
        }
        c = c.log();
        for (auto& val : c) val *= N;
        c = c.exp();
        for (int x = 0; x < int(c.size()); ++x) {
            b[x + N*p] = c[x] * mu;
        }
        return b;
    }
    Poly sqrt(int N) const {  // 262e0
        if (!size()) return {};
        if (deg() == -1) return Poly(N);
        int p = 0;
        while (at(p) == 0 && p < size()) ++p;
        if (p >= N) return {0};
        Poly fs(2*N);
        copy(this->begin() + p, this->end(), fs.begin());
        auto v = mod_sqrt(fs.at(0).x, M);
        if (p & 1 || v.empty()) return {};
        fs.resize(size() - p/2);
        fs *= fs.front().inv();
        fs = v[0] * (fs.log() / 2).exp();
        fs.insert(fs.begin(), p/2, 0);
        return fs;
    }
    Poly operator+() const { return *this; }
    Poly operator-() const {
        Poly fs(size());
        for (int i = 0; i < size(); ++i) fs[i] = -(*this)[i];
        return fs;
    }
    Poly operator+(const Poly &fs) const { return (Poly(*this) += fs); }
    Poly operator-(const Poly &fs) const { return (Poly(*this) -= fs); }
    Poly operator*(const Poly &fs) const { return (Poly(*this) *= fs); }
    Poly operator%(const Poly &fs) const { return (Poly(*this) %= fs); }
    Poly operator/(const Poly &fs) const { return (Poly(*this) /= fs); }
    Poly operator*(const num &a) const { return (Poly(*this) *= a); }
    Poly operator/(const num &a) const { return (Poly(*this) /= a); }
    friend Poly operator*(const num &a, const Poly &fs) { return fs * a; }
    // multipoint evaluation/interpolation
    friend Poly eval(const Poly& fs, const Poly& qs) { // da119a
        int N = int(qs.size());
        if (N == 0) return {};
        vector<Poly> up(2 * N);
        for (int x = 0; x < N; ++x)
            up[x + N] = Poly({0-qs[x], 1});
        for (int x = N-1; x >= 1; --x)
            up[x] = up[2 * x] * up[2 * x + 1];
        vector<Poly> down(2 * N);
        down[1] = fs % up[1];
        for (int x = 2; x < 2*N; ++x)
            down[x] = down[x/2] % up[x];
        Poly y(N);
        for (int x = 0; x < N; ++x)
            y[x] = (down[x + N].empty() ? 0 : down[x + N][0]);
        return y;
    }
    friend Poly interpolate(const Poly& fs, const Poly& qs) { // 798982
        int N = int(fs.size());
        vector<Poly> up(2 * N);
        for (int x = 0; x < N; ++x)
            up[x + N] = Poly({0-fs[x], 1});
        for (int x = N-1; x >= 1; --x)
            up[x] = up[2 * x] * up[2 * x + 1];
        Poly E = eval(up[1].differential(), fs);
        vector<Poly> down(2 * N);
        for (int x = 0; x < N; ++x)
            down[x + N] = Poly({qs[x] * E[x].inv()});
        for (int x = N-1; x >= 1; --x)
            down[x] = down[2*x] * up[2*x+1] + down[2*x+1] * up[2*x];
        return down[1];
    }
    friend Poly convolve_all(const vector<Poly>& fs, int l, int r) {
        if (r - l == 1) return fs[l];
        else {
            int md = (l + r) / 2;
            return convolve_all(fs, l, md) * convolve_all(fs, md, r);
        }
    }
    Poly bernoulli(int N) const { // 145ab7
        N += 5; Poly fs(N); fs[1] = 1;
        fs = fs.exp();
        copy(fs.begin()+1, fs.end(), fs.begin());
        fs = fs.inv();
        for (int x = 0; x < N; ++x) fs[x] *= fact[x];
        fs.resize(N - 5);
        return fs;
    }
    // x(x - 1)(x - 2)...(x - N + 1)
    Poly stirling_first(int N) const {
        if (N == 0) return {1};
        vector<Poly> P(N);
        for (int x = 0; x < N; ++x) P[x] = {-x, 1};
        return convolve_all(P, 0, N);
    }
    Poly stirling_second(int N) const {
        if (N == 0) return {1};
        Poly P(N), Q(N);
        for (int x = 0; x < N; ++x) {
            P[x] = (x & 1 ? -1 : 1) * ifact[x];
            Q[x] = num(x).pow(N-1) * ifact[x];
        }
        P *= Q; P.resize(N);
        return P;
    }
    Poly taylor_shift(int N, int K) const {
        Poly P(N), Q = *this; P[0] = 1;
        for (int i = 1; i < N; ++i) P[i] += P[i-1] * K;
        for (int i = 1; i < N; ++i) P[i] *= ifact[i];
        reverse(P.begin(), P.end());
        for (int i = 1; i < N; ++i) Q[i] *= fact[i];
        P *= Q;
        for (int i = 0; i < N; ++i) P[i] = P[N - 1 + i] * ifact[i];
        P.resize(N);
        return P;
    }
};

void prep(){
    fft_data.init(lim);
    invs[1] = 1;
    for (int i=2;i<lim;i++) invs[i] = -((num::M / i) * invs[num::M % i]);
    fact[0] = 1;
    for(int i=1;i<lim;i++) fact[i] = fact[i-1] * i;
    ifact[lim-1] = fact[lim-1].inv();
    for(int i=lim-2;i>=0;i--) ifact[i] = ifact[i+1] * (i+1);
}

num choose(int x, int y){
    if(x < 0 || y < 0 || x < y) return 0;
    return fact[x] * ifact[y] * ifact[x-y]; 
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    prep();
    int n, m;
    cin>>n>>m;
    vector<int>v(n), f(n);
    for(int i=0;i<n;i++) cin>>v[i], f[--v[i]]++;
    vector<int>ind;
    for(int i=0;i<n;i++) if(f[i]) ind.push_back(i);
    vector<vector<num>>Q(n);
    priority_queue<pair<int, int>>pq;
    for(int i : ind){
        Q[i].resize(f[i] + 1);
        for(int j=1;j<=f[i];j++) Q[i][j] = choose(f[i] - 1, j - 1) * fact[f[i]] * ifact[j];
        pq.push({-f[i]-1, i});
    }
    while(pq.size() > 1){
        auto [_1, i] = pq.top();
        pq.pop();
        auto [_2, j] = pq.top();
        pq.pop();
        if(i > j) swap(i, j);
        Q[i] = fft_data.convolve(Q[i], Q[j]);
        pq.push({-Q[i].size(), i});
    }
    auto q = Q[ind[0]];
    for(int i=1;i<=n;i++) q[i] *= fact[i];
    reverse(q.begin(), q.end());
    q.pop_back();
    vector<num>p1(n), p2(n);
    for(int i=0;i<n;i++){
        p1[i] = fact[i] * q[i];
        p2[i] = (i&1 ? -1 : 1) * ifact[i];
    }
    reverse(p2.begin(), p2.end());
    auto p = fft_data.convolve(p1, p2);
    vector<num>a(n);
    for(int i=0;i<n;i++) a[i] = p[n-1+i] * ifact[i];
    reverse(a.begin(), a.end());
    vector<vector<num>>N(n), D(n);
    for(int i=0;i<n;i++) N[i] = {a[i]};
    for(int i=0;i<n;i++) D[i] = {1, -i};
    for(int b=0;b<20;b++){
        if( (1<<b) >= n ) break;
        for(int i=0;i+(1<<b)<n;i+=(1<<(b+1))){
            auto x1 = fft_data.convolve(N[i], D[i+(1<<b)]);
            auto x2 = fft_data.convolve(D[i], N[i+(1<<b)]);
            D[i] = fft_data.convolve(D[i], D[i+(1<<b)]);
            for(int j=0;j<(int)x2.size();j++) x1[j] += x2[j];
            N[i] = x1;
        }
    }

    Poly<mod>X(N[0]), Y(D[0]);
    Y.resize(max(n, m) + 1);
    Poly<mod>ans = X * Y.inv();
    ans.resize(m + 1);
    ans.erase(ans.begin());
    for(auto u : ans) cout<<u.x<<" ";
    cout<<"\n";

    return 0;
}
