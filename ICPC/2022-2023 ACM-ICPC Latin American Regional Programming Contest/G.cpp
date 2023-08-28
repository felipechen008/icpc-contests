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
using P = Point<lint>;

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

bool inHull(const vector<P> &l, P p, bool strict = false) {
	int a = 1, b = l.size() - 1, r = !strict;
	if (l.size() < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}

vector<P> convexHull(vector<P> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	vector<P> h(pts.size()+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

void reorder_polygon(vector<P> & p){
    size_t pos = 0;
    for(size_t i = 1; i < p.size(); i++){
        if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
            pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

vector<P> minkowski(vector<P> p, vector<P> q){
    // the first vertex must be the lowest
    reorder_polygon(p);
    reorder_polygon(q);
    // we must ensure cyclic indexing
    p.push_back(p[0]);
    p.push_back(p[1]);
    q.push_back(q[0]);
    q.push_back(q[1]);
    // main part
    vector<P> result;
    size_t i = 0, j = 0;
    while(i < p.size() - 2 || j < q.size() - 2){
        result.push_back(p[i] + q[j]);
        auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
        if(cross >= 0)
            ++i;
        if(cross <= 0)
            ++j;
    }
    return result;
}

vector<P>mul(vector<P>p, lint c){
    for(auto& pnt : p) pnt.x *= c, pnt.y *= c;
    return p;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, t;
    cin>>n;
    vector<P>p(n);
    for(int i=0;i<n;i++) cin>>p[i].x>>p[i].y;
    cin>>m;
    vector<P>q(m);
    for(int i=0;i<m;i++) cin>>q[i].x>>q[i].y;
    vector<P>u = convexHull(minkowski(p, q));
    vector<P>v = convexHull(minkowski(mul(p, 2), mul(q, -1)));
    vector<P>w = convexHull(minkowski(mul(p, -1), mul(q, 2)));
    cin>>t;
    while(t--){
        P pnt;
        cin>>pnt.x>>pnt.y;
        int ans = inHull(u, pnt * 2) + inHull(v, pnt) + inHull(w, pnt);
        if(ans) cout<<"Y";
        else cout<<"N";
    }
    cout<<"\n";
    return 0;
}
