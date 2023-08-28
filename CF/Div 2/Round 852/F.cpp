#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<typename T> struct segmax {
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
    segmax(int _n = 0, T def = unit) : s(2*_n, def), n(_n) {}
	void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
    T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

template<typename T> struct segmin {
	static constexpr T unit = INT_MAX;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
    segmin(int _n = 0, T def = unit) : s(2*_n, def), n(_n) {}
	void update(int pos, T val) {
        pos += n;
        for (s[pos] = f(s[pos], val); pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
    T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};


int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin>>n>>q;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int>v = a, b = a, c = a, f(n);
    sort(v.begin(), v.end());
    for(int i=0;i<n;i++){
        b[i] = int(lower_bound(v.begin(), v.end(), a[i]) - v.begin());
        c[i] = b[i] + f[b[i]]++;
    }
    vector<vector<pair<int, int>>>qr(n);
    for(int i=0;i<q;i++){
        int l, r;
        cin>>l>>r;
        l--, r--;
        qr[r].emplace_back(l, i);
    }

    segmax<int>ind(n);
    segmin<int>dp(n);
    vector<int>ans(q);

    for(int i=0;i<n;i++){
        {
            int lo = b[i], hi = int(1e9 + 10);
            while(true){
                hi = int(upper_bound(v.begin(), v.end(), hi) - v.begin());
                int j = ind.query(lo, hi);
                if(j < 0) break;
                dp.update(j, a[j] - a[i]);
                hi = (a[i] + a[j]) / 2;
                if(a[i] == a[j]) break;
            }
        }
        {
            int lo = 0, hi = b[i];
            while(true){
                lo = int(lower_bound(v.begin(), v.end(), lo) - v.begin());
                int j = ind.query(lo, hi);
                if(j < 0) break;
                dp.update(j, a[i] - a[j]);
                lo = (a[i] + a[j] + 1) / 2;
            }
        }
        ind.update(c[i], i);
        for(auto [l, j] : qr[i]){
            ans[j] = dp.query(l, i);
        }
    }
    for(int u : ans) cout<<u<<"\n";
    return 0;
}
