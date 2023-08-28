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
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                y[i] += A[i][j] * b[j];
            }
        }
        return y;
    }
    Matrix& operator*=(const Matrix& r) { return *this = *this * r; }
    Matrix pow(int n) const {
        assert(h() == w());
        Matrix x = *this, r(h(), vector<T>(w()));
        for (int i = 0; i < h(); ++i) r[i][i] = T(1);
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
};

template<typename T> struct gaussian_elimination {
    int N, M;
    Matrix<T> A, E;
    vector<int> pivot;
    int rank, nullity, sgn;
    // O(std::min(N, M)NM)
    gaussian_elimination(const Matrix<T>& A_) : A(A_) {
        N = A.size(), M = A[0].size();
        E = Matrix<T>(N, vector<T>(N));
        for (int i = 0; i < N; ++i) {
            E[i][i] = 1;
        }
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
                for (int j = col; j < M; ++j) {
                    A[i][j] -= c * A[row][j];
                }
                for (int j = 0; j < N; ++j) {
                    E[i][j] -= c * E[row][j];
                }
            }
            pivot[col] = row++;
            ++rank, --nullity;
        }
    }
    // O(N^2 + M)
    pair<bool, vector<T>> solve(vector<T> b, bool reduced = false) const {
        assert(N == b.size());
        if (reduced == false) {
            b = E * b;
        }
        vector<T> x(M);
        for (int j = 0; j < M; ++j) {
            if (pivot[j] == -1) continue;
            x[j] = b[pivot[j]] / A[pivot[j]][j];
            b[pivot[j]] = 0;
        }
        for (int i = 0; i < N; ++i) {
            if (b[i] != 0) return {false, x};
        }
        return {true, x};
    }
    // O(nullity * NM)
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
    // O(N^3)
    Matrix<T> inverse() const {
        assert(N == M); assert(rank == N);
        Matrix<T> res(N, vector<T>(N));
        vector<T> e(N);
        for (int i = 0; i < N; ++i) {
            e[i] = 1;
            auto x = solve(e).second;
            for (int j = 0; j < N; ++j) {
                res[j][i] = x[j];
            }
            e[i] = 0;
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    num d6 = num(6).inv();
    Matrix<num>A(7, vector<num>(7));
    for(int i=0;i<5;i++) A[i][i+1] = 1;
    for(int i=0;i<6;i++) A[5][i] = d6;
    A[5][6] = 1;
    A[6][6] = 1;

    vector<num>exp;
    {
        // calculate expected value of 10^9 - i, for 1 <= i <= 6
        Matrix<num>B(7, vector<num>(7));
        for(int i=0;i<6;i++) B[i][5-i] = 1;
        B[6][6] = 1;

        auto res = A.pow( int(1e9 - 7) ) * B;
        vector<vector<num>>dp(6, vector<num>(7));
        for(int i=0;i<6;i++) dp[i] = res[5 - i];

        Matrix<num>C(6, vector<num>(6));
        vector<num>D(6);
        for(int i=0;i<6;i++){
            C[i][i] += 1;
            D[i] += 1;

            for(int j=1;j<=6;j++){
                if(i + j < 6){
                    C[i][i+j] -= 1 * d6;
                }
                else if(i + j > 6){
                    int c = i + j - 7;
                    for(int k=0;k<6;k++) C[i][k] -= dp[c][k] * d6;
                    D[i] += dp[c][6] * d6;
                }
            }
        }
        gaussian_elimination g(C);
        auto [w, x] = g.solve(D);
        exp = x;
    }

    reverse(exp.begin(), exp.end());
    // value of exp {355656315, 199596252, 436599042, 686943055, 519765314, 291034221};

    int r;
    cin>>r;
    r--;
    if(r < 6){
        cout<<exp[r]<<"\n";
        return 0;
    }

    Matrix<num>B(7, vector<num>(1));
    for(int i=0;i<6;i++) B[i][0] = exp[i];
    B[6][0] = 1;

    Matrix res = A.pow(r - 5) * B;

    cout<<res[5][0]<<"\n";

    return 0;
}
