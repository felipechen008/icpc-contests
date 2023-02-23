#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

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
	int lower_bound(T sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= (int)s.size() && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

template<typename T> struct FT2 {
	vector<vector<int>> ys; vector<FT<T>> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < (int)ys.size(); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for(auto &v : ys){
			sort(v.begin(), v.end());
			v.resize(unique(v.begin(),v.end()) - v.begin());
			ft.emplace_back(v.size());
		}
	}
	int ind(int x, int y) {
		return (int)(lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin()); }
	void update(int x, int y, T dif) {
		for (; x < ys.size(); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	T query(int x, int y) {
		T sum = 0;
		for (; x; x &= x - 1) sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        int lim = n + 5;
        vector<FT2<int>>zero(3, FT2<int>(2*lim)), one(3, FT2<int>(2*lim));
        zero[0].fakeUpdate(n, n);
        vector<int>val(n), rest(n), adj(n);
        int pos = 0, neg = 0, cnt = 0; 
        lint ans = 0;
        for(int l=0,r=0;r<n;r++){
            if(s[r] == '+'){
                if( (r - l) & 1 ){
                    for(int j=l;j<r;j++){
                        int k = rest[j];
                        one[k].fakeUpdate(val[j], val[j] + adj[j]);
                        zero[k].fakeUpdate(val[j], val[j] + adj[j]);
                    }
                }
                l = r + 1;
                pos++;
            }
            else neg++;
            if(s[r] == '-' && (r - l) & 1 ) cnt++;
            
            rest[r] = ( (neg - pos) % 3 + 3 ) % 3;
            val[r] = (neg - pos - rest[r]) / 3 + n;
            adj[r] = cnt;
            int k = rest[r];

            if(s[r] == '-' && (r - l) % 2 == 0){
                one[k].fakeUpdate(val[r], val[r] + adj[r]);
            }
            else{
                zero[k].fakeUpdate(val[r], val[r] + adj[r]);
            }
        }

        for(int i=0;i<3;i++) zero[i].init(), one[i].init();
        zero[0].update(n, n, 1);

        for(int l=0,r=0;r<n;r++){
            if(s[r] == '+'){
                if( (r - l) & 1 ){
                    for(int j=l;j<r;j+=2){
                        int k = rest[j];
                        one[k].update(val[j], val[j] + adj[j], -1);
                        zero[k].update(val[j], val[j] + adj[j], 1);
                    }
                }
                l = r + 1;
            }
            int k = rest[r];
            ans += one[k].query(val[r] + 1, val[r] + adj[r]);
            ans += zero[k].query(val[r] + 1, val[r] + adj[r] + 1);

            if(s[r] == '-' && (r - l) % 2 == 0){
                one[k].update(val[r], val[r] + adj[r], 1);
            }
            else{
                zero[k].update(val[r], val[r] + adj[r], 1);
            }
        }


        cout<<ans<<"\n";
    }

    return 0;
}
