#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

using num = long long;
struct frac { /// start-hash
    num n, d;
    frac() : n(0), d(1) { }
    frac(num _n, num _d = 1): n(_n), d(_d){
        num g = gcd(n, d); n /= g, d /= g;
        if (d < 0) n *= -1, d *= -1;
        assert(d != 0);
    }
    friend bool operator<(const frac& l, const frac& r) { return __int128(1) * l.n * r.d < __int128(1) * r.n * l.d; }
    friend bool operator==(const frac& l, const frac& r) { return l.n == r.n && l.d == r.d; }
    friend bool operator!=(const frac& l, const frac& r) { return !(l == r); }
    friend frac operator+(const frac& l, const frac& r) { 
    	num g = gcd(l.d, r.d);
    	return frac( r.d / g * l.n + l.d / g * r.n, l.d / g * r.d);
    }
    friend frac operator-(const frac& l, const frac& r) { 
    	num g = gcd(l.d, r.d);
    	return frac( r.d / g * l.n - l.d / g * r.n, l.d / g * r.d);
    }
    friend frac operator*(const frac& l, const frac& r) { return frac(l.n * r.n, l.d * r.d); }
    friend frac operator/(const frac& l, const frac& r) { return l * frac(r.d, r.n); }
    friend frac& operator+=(frac& l, const frac& r) { return l = l+r; }
    friend frac& operator-=(frac& l, const frac& r) { return l = l-r; }
    template<class T> friend frac& operator*=(frac& l, const T& r) { return l = l*r; }
    template<class T> friend frac& operator/=(frac& l, const T& r) { return l = l/r; }
    friend ostream& operator<<(ostream& strm, const frac& a) {
        strm << a.n << "/" << a.d;
        return strm;
    }
};

struct Line {
	mutable lint k, m;
    mutable frac p = frac();
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(frac x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	frac div(lint a, lint b) { // floored division
		return frac(a, b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? frac(linf, 1) : frac(-linf, 1);
		else x->p = div(y->m - x->m, x->k - y->k);
		return !(x->p < y->p);
	}
	void add(lint k, lint m) {
		auto z = insert({k, m, frac(0, 1)}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && !( (--x)->p < y->p ) )
			isect(x, erase(y));
	}
	lint query(lint a, lint b) {
		assert(!empty());
		auto l = *lower_bound(frac(a, b));
		return l.k * a + l.m * b;
	}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin>>q;
    LineContainer g, h, i;
    while(q--){
        lint x, y, a, b;
        cin>>x>>y>>a>>b;
        g.add(x, y);
        h.add(x, -y);
        i.add(x, 0);
        if(b > 0){
            cout<<g.query(a, b)<<"\n";
        }
        else if(!b){
            cout<<i.query(a, 1)<<"\n";
        }
        else{
            cout<<h.query(a, -b)<<"\n";
        }
    }

    return 0;
}
