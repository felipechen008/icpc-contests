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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    P b, e;
    cin>>b.x>>b.y>>e.x>>e.y;
    vector<P>p(n);
    vector<lint>r(n);
    for(int i=0;i<n;i++) cin>>p[i].x>>p[i].y>>r[i];
    vector<vector<int>>g(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            lint d = (p[i] - p[j]).dist2();
            lint sum = r[i] + r[j], dif = r[i] - r[j];
            if(sum * sum < d || dif * dif > d) continue;
            g[i].push_back(j);
            g[j].push_back(i);
        }
    }
    int bid = -1, eid = -1;
    for(int i=0;i<n;i++){
        lint d = (p[i] - b).dist2();
        if(d == r[i] * r[i]) bid = i;
    }
    for(int i=0;i<n;i++){
        lint d = (p[i] - e).dist2();
        if(d == r[i] * r[i]) eid = i;
    }
    if(bid == -1 || eid == -1) cout<<"No\n";
    else{
        vector<bool>vis(n);
        auto dfs = [&](auto& self, int u)->void {
            vis[u] = 1;
            for(int v : g[u]){
                if(vis[v]) continue;
                self(self, v);
            }
        };
        dfs(dfs, bid);
        if(vis[eid]) cout<<"Yes\n";
        else cout<<"No\n";
    }

    return 0;
}
