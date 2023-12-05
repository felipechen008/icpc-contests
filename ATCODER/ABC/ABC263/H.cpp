#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};
using P = Point<double>;

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
    return (double)(b-a).cross(p-a)/(b-a).dist();
}

template<class P>
P lineProj(P a, P b, P p, bool refl=false) {
    P v = b - a;
    return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}

vector<P> circleLine(P c, double r, P a, P b) {
    double h2 = r*r - a.cross(b,c)*a.cross(b,c)/(b-a).dist2();
    if (h2 < 0) return {};
    P p = lineProj(a, b, c), h = (b-a).unit() * sqrt(h2);
    if (h2 == 0) return {p};
    return {p - h, p + h};
}
const double pi = acos(-1.0);

template<typename T> struct FT { // 8b7639
    vector<T> s;
    FT(int n) : s(n) {}
    FT(const vector<T>& A) : s(A) {
        const int N = int(s.size());
        for (int a = 0; a < N; ++a)
            if ((a | (a + 1)) < N) s[a | (a + 1)] += s[a];
    }
    void update(int pos, T dif) { // a[pos] += dif
        for (; pos < (int)s.size(); pos |= pos + 1) s[pos] += dif;
    }
    T query(int pos) { // sum of values in [0, pos)
        T res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    // min pos st sum of [0, pos] >= sum. Returns n if no sum
    int lower_bound(T sum) { //is >= sum, or -1 if empty sum is.
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)
            if (pos + pw <= (int)s.size() && s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        return pos;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; lint k;
    cin>>n>>k;
    vector<int>a(n), b(n), c(n);
    for(int i=0;i<n;i++) cin>>a[i]>>b[i]>>c[i];
    vector<P>be(n), en(n);
    for(int i=0;i<n;i++){
        if(!a[i]){
            be[i] = P(-1, - 1.0 * c[i] / b[i]);
            en[i] = P(1, - 1.0 * c[i] / b[i]);
        }
        else if(!b[i]){
            be[i] = P(- 1.0 * c[i] / a[i], -1);
            en[i] = P(- 1.0 * c[i] / a[i], 1);
        }
        else if(!c[i]){
            be[i] = P(-1, 1.0 * a[i] / b[i]);
            en[i] = P(1, -1.0 * a[i] / b[i]);
        }
        else{
            be[i] = P(0, - 1.0 * c[i] / b[i]);
            en[i] = P(- 1.0 * c[i] / a[i], 0);
        }
    }

    double lo = 0, hi = 5e6;
    P orig = P(0, 0);
    for(int z=0;z<150;z++){
        double mid = (lo + hi) / 2;
        vector<vector<P>>inter(n);
        for(int i=0;i<n;i++) inter[i] = circleLine(orig, mid, be[i], en[i]);
        vector<pair<double, double>>ang;
        for(int i=0;i<n;i++){
            if(inter[i].size() < 2) continue;
            double x = inter[i][0].angle();
            double y = inter[i][1].angle();
            if(x > y) swap(x, y);
            ang.push_back({x, y});
        }
        sort(ang.begin(), ang.end());
        vector<pair<double, int>>v;
        int sz = (int)ang.size();
        for(int i=0;i<sz;i++){
            auto [x, y] = ang[i];
            v.emplace_back(y, i);
        }
        sort(v.begin(), v.end());
        lint cur = 0;
        FT<int>seg(sz);
        int j = 0;
        for(int i=0;i<sz;i++){
            while(v[j].st < ang[i].st){
                seg.update(v[j].nd, -1);
                cur += seg.query(sz) - seg.query(v[j++].nd);               
            }
            seg.update(i, 1);
        }
        while(j < sz){
            seg.update(v[j].nd, -1);
            cur += seg.query(sz) - seg.query(v[j++].nd);
        }
        if(cur < k) lo = mid;
        else hi = mid;
    }
    cout<<fixed<<setprecision(9);
    cout<<hi<<"\n";
    return 0;
}
