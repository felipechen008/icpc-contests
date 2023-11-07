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
    Matrix pow(int n) const {
        assert(h() == w());
        Matrix x = *this, r(h(), vector<T>(w()));
        for (int i = 0; i < h(); ++i) r[i][i] = T(1);
        while (n) { if (n & 1) r *= x; x *= x; n >>= 1; }
        return r;
    }
};

template<typename T> struct gaussian_elimination {
    int N, M;
    Matrix<T> A, E;
    vector<int> pivot;
    int rank, nullity, sgn;
    gaussian_elimination(const Matrix<T>& A_) : A(A_) {
        N = A.size(), M = A[0].size();
        E = Matrix<T>(N, vector<T>(N));
        for (int i = 0; i < N; ++i) E[i][i] = 1;
        rank = 0, nullity = M, sgn = 0;
        pivot.assign(M, -1);
        for (int col = 0, row = 0; col < M && row < N; ++col) {
            int sel = -1;
            for (int i = row; i < N; ++i) {
                if (A[i][col] != 0) {
                    sel = i;
                    break;
                }
            }
            if (sel == -1) continue;
            if (sel != row) {
                sgn += 1;
                swap(A[sel], A[row]);
                swap(E[sel], E[row]);
            }
            for (int i = 0; i < N; ++i) {
                if (i == row) continue;
                T c = A[i][col] / A[row][col];
                for (int j = col; j < M; ++j)
                    A[i][j] -= c * A[row][j];
                for (int j = 0; j < N; ++j)
                    E[i][j] -= c * E[row][j];
            }
            pivot[col] = row++;
            ++rank, --nullity;
        }
    }
    pair<bool, vector<T>> solve(vector<T> b, bool reduced = false) const {
        if (reduced == false) b = E * b;
        vector<T> x(M);
        for (int j = 0; j < M; ++j) {
            if (pivot[j] == -1) continue;
            x[j] = b[pivot[j]] / A[pivot[j]][j];
            b[pivot[j]] = 0;
        }
        for (int i = 0; i < N; ++i) 
            if (b[i] != 0) return {false, x};
        return {true, x};
    }
    vector<vector<T>> kernel_basis() const {
        vector<vector<T>> basis;
        vector<T> e(M);
        for (int j = 0; j < M; ++j) {
            if (pivot[j] != -1) continue;
            e[j] = 1;
            auto y = solve(A * e, true).second;
            e[j] = 0, y[j] = -1;
            basis.push_back(y);
        }
        return basis;
    }
    Matrix<T> inverse() const {
        assert(N == M); assert(rank == N);
        Matrix<T> res(N, vector<T>(N));
        vector<T> e(N);
        for (int i = 0; i < N; ++i) {
            e[i] = 1;
            auto x = solve(e).second;
            for (int j = 0; j < N; ++j)
                res[j][i] = x[j];
            e[i] = 0;
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin>>n>>m;

    vector<num>fac(n + 1), ifac(n + 1);
    fac[0] = 1;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i;
    ifac[n] = fac[n].inv();
    for(int i=n-1;i>=0;i--) ifac[i] = ifac[i+1] * (i + 1); 

    vector<pair<int, int>>e(m);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        e[i] = {a, b};
    }
    // probability that mask is a tree in k op
    vector<num>cnt(1<<n);
    vector<int>id(n);
    for(int mask=1;mask<1<<n;mask++){
        vector<int>cur;
        int sz = 0;
        for(int i=0;i<n;i++){
            if(mask>>i&1){
                cur.push_back(i);
                id[i] = sz++;
            }
        }
        Matrix<num>g(sz, vector<num>(sz));
        for(auto [a, b] : e){
            int x = mask>>a&1, y = mask>>b&1;
            if(x && y){
                a = id[a], b = id[b];
                if(a < sz - 1) g[a][a] += 1;
                if(b < sz - 1) g[b][b] += 1;
                if(a < sz - 1 && b < sz - 1) g[a][b] -= 1, g[b][a] -= 1;
            }
        }
        gaussian_elimination<num>gauss(g);
        cnt[mask] = 1;
        for(int i=0;i<sz-1;i++) cnt[mask] *= gauss.A[i][i];
    }

    vector<vector<num>>dp(n, vector<num>(1<<n));
    dp[1] = cnt;
    for(int i=2;i<n;i++){
        for(int mask=0;mask<1<<n;mask++){
            for(int submask=mask;submask;submask=(submask - 1)&mask){
                dp[i][mask] += dp[i-1][submask] * cnt[mask ^ submask];
            }
        }
    }
    int tot = (1<<n) - 1;
    num den = 1, inverse = num(m).inv();

    for(int i=n-1;i;i--){
        den *= inverse;
        num ans = dp[i][tot] * ifac[i] * fac[n-i] * den;
        cout<<ans<<"\n";
    }


    return 0;
}
