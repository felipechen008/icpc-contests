#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct Line {
	mutable lint k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(lint x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const lint inf = LLONG_MAX;
	lint div(lint a, lint b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(lint k, lint m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	lint query(lint x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin>>n;
    vector<pair<int, int>>a(n);
    for(int i=0;i<n;i++){
        int x, y;
        cin>>x>>y;
        a[i] = {x, y};
    }
    cin>>m;
    vector<pair<int, int>>b(m);
    for(int i=0;i<m;i++){
        int x, y;
        cin>>x>>y;
        b[i] = {x, y};
    }
    vector<int>lo(n), hi(n, m-1);
    for(int z=0;z<18;z++){
        vector<vector<int>>ind(m);
        for(int i=0;i<n;i++){
            int mid = (lo[i] + hi[i]) / 2;
            ind[mid].push_back(i);
        }
        LineContainer g;
        for(int i=0;i<m;i++){
            {
                auto [x, y] = b[i];
                g.add(x, y);
            }
            for(int j : ind[i]){
                auto [x, y] = a[j];
                if(y < g.query(x)) hi[j] = i - 1;
                else lo[j] = i + 1;
            }
        }
    }
    vector<vector<int>>ans(m);
    for(int i=0;i<n;i++){
        if(lo[i] == m) continue;
        ans[lo[i]].push_back(i + 1);
    }
    for(auto& v : ans){
        cout<<size(v)<<" ";
        for(int u : v) cout<<u<<" ";
        cout<<"\n";
    }

    return 0;
}
