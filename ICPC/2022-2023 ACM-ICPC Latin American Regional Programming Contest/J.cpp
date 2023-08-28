#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct frac { /// start-hash
    lint n, d;
    frac() : n(0), d(1) { }
    frac(lint _n, lint _d = 1): n(_n), d(_d){
        lint g = gcd(n, d); n /= g, d /= g;
        if (d < 0) n *= -1, d *= -1;
        assert(d != 0);
    }
    friend bool operator<(const frac& l, const frac& r) { return __int128(1) * l.n * r.d < __int128(1) * r.n * l.d; }
    friend bool operator==(const frac& l, const frac& r) { return l.n == r.n && l.d == r.d; }
    friend bool operator!=(const frac& l, const frac& r) { return !(l == r); }
    friend frac operator+(const frac& l, const frac& r) { 
    	lint g = gcd(l.d, r.d);
    	return frac( r.d / g * l.n + l.d / g * r.n, l.d / g * r.d);
    }
    friend frac operator-(const frac& l, const frac& r) { 
    	lint g = gcd(l.d, r.d);
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

struct intersection{
    frac x;
    lint c, d;
    int a, b;
    intersection(){}
    intersection(array<lint, 3>p, array<lint, 3>q){
        if(p[0] < q[0]) swap(p, q);
        x = frac(q[1] - p[1], p[0] - q[0]);
        c = p[0], a = p[2];
        d = q[0], b = q[2];
                                                                                                   
    }
    bool operator<(const intersection& o) const {
        return make_tuple(x, -c, -d, -a, b) < make_tuple(o.x, -o.c, -o.d, -o.a, o.b);
    }
};

template<typename T> struct FT { // 8b7639
	vector<T> s;
	FT(int n) : s(n) {}
	FT(const vector<T>& A) : s(int(A.size())) {
		const int N = int(A.size());
		for (int pos = 0; pos < N; ++pos) {
			s[pos] += A[pos];
			int nxt = (pos | (pos + 1));
			if (nxt < N) s[nxt] += s[pos];
		}
	}
	void update(int pos, T dif) { // a[pos] += dif
		for (; pos < (int)s.size(); pos |= pos + 1) s[pos] += dif;
	}
	T query(int pos) { // sum of values in [0, pos)
		T res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int r;
    cin>>r;
    vector<array<lint, 3>>runners(r);
    for(int i=0;i<r;i++){
        lint t, s;
        cin>>t>>s;
        runners[i] = {s, - t * s, i};
    }

    int p;
    cin>>p;
    vector<array<lint, 3>>photos(p);
    for(int i=0;i<p;i++){
        int u, a, b;
        cin>>u>>a>>b;
        photos[i] = {u, a, b};
    }
    sort(photos.begin(), photos.end());

    {
        vector<intersection>inter;
        for(int i=0;i<r;i++){
            for(int j=i+1;j<r;j++){
                if(runners[i][0] == runners[j][0]) continue;
                inter.push_back({runners[i], runners[j]});
            }
        }

        sort(inter.begin(), inter.end());

        vector<int>pos(r), revpos(r);
        iota(pos.begin(), pos.end(), 0);
        sort(pos.begin(), pos.end(), [&](int i, int j){
            if(runners[i][1] == runners[j][1]){
                if(runners[i][0] == runners[j][0]){
                    return i < j;
                }
                return runners[i][0] < runners[j][0];
            }
            return runners[i][1] < runners[j][1];
        });

        for(int i=0;i<r;i++) revpos[pos[i]] = i;
        vector<array<lint, 3>>bad;

        int i = 0;
        while(i < int(size(inter)) && !(frac(0) < inter[i].x)) i++;
        for(auto [u, ll, rr] : photos){
            while(i < int(size(inter)) && inter[i].x < frac(u)){
                int a = revpos[inter[i].a]; 
                int b = revpos[inter[i].b]; 
                swap(pos[a], pos[b]);
                revpos[inter[i].a] = b;
                revpos[inter[i].b] = a;
                i++;
            }

            int lo = 0, hi = r - 1;
            while(lo <= hi){
                int mid = (lo + hi) / 2;
                int j = pos[mid];
                lint y = runners[j][0] * u + runners[j][1];
                if(y >= ll) hi = mid - 1;
                else lo = mid + 1;
            }
            if(lo == r){
                bad.push_back({u, ll, rr});
            }
            else{
                int j = pos[lo];
                lint y = runners[j][0] * u + runners[j][1];
                if(y > rr) bad.push_back({u, ll, rr});
            }
        }
        swap(bad, photos);
        p = int(size(photos));
    }
    {
        int q;
        cin>>q;
        vector<array<lint, 3>>queries(q);
        for(int i=0;i<q;i++){
            lint t, s;
            cin>>t>>s;
            queries[i] = {s, - t * s, i};
        }
        swap(queries, runners);
        r = int(size(runners));
    }

    {
        vector<intersection>inter;
        for(int i=0;i<r;i++){
            for(int j=i+1;j<r;j++){
                if(runners[i][0] == runners[j][0]) continue;
                inter.push_back({runners[i], runners[j]});
            }
        }

        sort(inter.begin(), inter.end());

        vector<int>pos(r), revpos(r);
        iota(pos.begin(), pos.end(), 0);
        sort(pos.begin(), pos.end(), [&](int i, int j){
            if(runners[i][1] == runners[j][1]){
                if(runners[i][0] == runners[j][0]){
                    return i < j;
                }
                return runners[i][0] < runners[j][0];
            }
            return runners[i][1] < runners[j][1];
        });

        for(int i=0;i<r;i++) revpos[pos[i]] = i;

        vector<int>last(r, -1);
        vector<vector<array<int, 3>>>runners_intervals(r);

        int i = 0;
        while(i < int(size(inter)) && !(frac(0) < inter[i].x)) i++;
        vector<pair<int, int>>intervals(p);
        for(int j=0;j<p;j++){
            auto [u, ll, rr] = photos[j];
            while(i < int(size(inter)) && inter[i].x < frac(u)){
                int c = inter[i].a, d = inter[i].b;
                int a = revpos[c], b = revpos[d]; 
                runners_intervals[c].push_back({last[c] + 1, j + 1, a});
                runners_intervals[d].push_back({last[d] + 1, j + 1, b});
                last[c] = last[d] = j;
                swap(pos[a], pos[b]);
                revpos[c] = b, revpos[d] = a;
                i++;
            }

            int lo = 0, hi = r - 1;
            while(lo <= hi){
                int mid = (lo + hi) / 2;
                int k = pos[mid];
                lint y = runners[k][0] * u + runners[k][1];
                if(y >= ll) hi = mid - 1;
                else lo = mid + 1;
            }
            int left = lo;
            lo = 0, hi = r - 1;

            while(lo <= hi){
                int mid = (lo + hi) / 2;
                int k = pos[mid];
                lint y = runners[k][0] * u + runners[k][1];
                if(y <= rr) lo = mid + 1;
                else hi = mid - 1;
            }
            int right = hi;
            intervals[j] = {left, right};
        }
        vector<vector<array<int, 3>>>queries(p + 2);
        for(int i=0;i<r;i++){
            runners_intervals[i].push_back({last[i] + 1, p + 1, revpos[i]});
            for(auto [ll, rr, x] : runners_intervals[i]){
                queries[ll].push_back({x, -1, i});
                queries[rr].push_back({x, 1, i});
            }
        }
        vector<int>cnt(r);
        FT<int>seg(r + 1);
        for(int i=0;i<=p + 1;i++){
            for(auto [x, y, id] : queries[i]){
                cnt[id] += seg.query(x + 1) * y;
            }
            if(i && i <= p){
                auto [left, right] = intervals[i - 1];
                if(left <= right){
                    seg.update(left, 1);
                    seg.update(right + 1, -1);
                }
            }
        }

        for(int i=0;i<r;i++){
            cout<<p - cnt[i]<<"\n";
        }
    }

    return 0;
}
