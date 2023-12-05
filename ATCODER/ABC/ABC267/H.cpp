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

//(MOD,3) := (M1:897581057),(M3:985661441),(M5:935329793)
using num = modnum<998244353U>;
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
        int K = N + M - 1, S = nxt_pow2(K); init(S);
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
FFT<num>fft;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    fft.init(1<<20);
    int n, m;
    cin>>n>>m;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
    vector<vector<num>>poly(n), poly2(n);
    for(int i=0;i<n;i++){
        poly[i] = poly2[i] = vector<num>(a[i] + 1);
        poly[i][0] = poly2[i][0] = 1;
        poly[i][a[i]] = 1;
        poly2[i][a[i]] = -1;
        pq.push({a[i], i});
    }
    vector<int>c = a;
    for(int z=1;z<n;z++){
        auto [w1, i] = pq.top();
        pq.pop();
        auto [w2, j] = pq.top();
        pq.pop();
        if(i > j) swap(i, j);
        c[i] += c[j];
        poly[i] = fft.convolve(poly[i], poly[j]);
        poly2[i] = fft.convolve(poly2[i], poly2[j]);
        pq.push({c[i], i});
    }
    if(poly[0].size() < m + 1) cout<<"0\n";
    else{
        num ans = ( poly[0][m] - poly2[0][m] ) * num(2).inv();
        cout<<ans.x<<"\n"; 
    }
    return 0;
}
