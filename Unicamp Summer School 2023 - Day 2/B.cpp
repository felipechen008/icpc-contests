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
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

#define eps 1e-8
typedef Point<double> P;

struct Line {
    P P1, P2;
    // Right hand side of the ray P1 -> P2
    explicit Line(P a = P(), P b = P()) : P1(a), P2(b) {};
    P intpo(Line y) {
        pair<int, P> r = lineInter(P1, P2, y.P1, y.P2);
        assert(r.first == 1);
        return r.second;
    }
    P dir() {
        return P2 - P1;
    }
    bool contains(P x) {
        return (P2 - P1).cross(x - P1) < eps;
    }
    bool out(P x) {
        return !contains(x);
    }
}; 

template<class T>
bool mycmp(Point<T> a, Point<T> b) {
    // return atan2(a.y, a.x) < atan2(b.y, b.x);
    if (a.x * b.x < 0)  return a.x < 0;
    if (abs(a.x) < eps) {
        if (abs(b.x) < eps)     return a.y > 0 && b.y < 0;
        if (b.x < 0)    return a.y > 0;
        if (b.x > 0)    return true;
    }
    if (abs(b.x) < eps) {
        if (a.x < 0)    return b.y < 0;
        if (a.x > 0)    return false;
    }
    return a.cross(b) > 0;
}

bool cmp(Line a, Line b) {
    return mycmp(a.dir(), b.dir());
}

double Intersection_Area(vector <Line> b) {
    sort(b.begin(), b.end(), cmp);
    int n = b.size();
    int q = 1, h = 0, i;
    vector <Line> c(b.size() + 10);
    for (i = 0; i < n; i++) {
        while (q < h && b[i].out(c[h].intpo(c[h - 1]))) h--;
        while (q < h && b[i].out(c[q].intpo(c[q + 1]))) q++;
        c[++h] = b[i];
        if (q < h && abs(c[h].dir().cross(c[h - 1].dir())) < eps) {
            if (c[h].dir().dot(c[h - 1].dir()) > 0) {
                h--;
                if (b[i].out(c[h].P1))  c[h] = b[i];
            }else {
                // The area is either 0 or infinite.
                // If you have a bounding box, then the area is definitely 0. 
                return 0;
            }
        }
    }
    while (q < h - 1 && c[q].out(c[h].intpo(c[h - 1]))) h--;
    while (q < h - 1 && c[h].out(c[q].intpo(c[q + 1]))) q++;
    // Intersection is empty. This is sometimes different from the case when
    // the intersection area is 0. 
    if (h - q <= 1) return 0;
    c[h + 1] = c[q];
    vector <P> s;
    for (i = q; i <= h; i++)    s.push_back(c[i].intpo(c[i + 1]));
    s.push_back(s[0]);
    double ans = 0;
    for (i = 0; i < (int) s.size() - 1; i++)    ans += s[i].cross(s[i + 1]);
    return ans / 2;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<P>pnt(n);
    for(int i=0;i<n;i++) cin>>pnt[i].x>>pnt[i].y;
    vector<Line>lines(n);
    for(int i=0;i<n;i++) lines[i] = Line(pnt[i], pnt[(i+1) % n]);
    cout<<fixed<<setprecision(8);
    cout<<Intersection_Area(lines)<<"\n";

    return 0;
}
