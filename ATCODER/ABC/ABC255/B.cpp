#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int n, k;
	cin>>n>>k;
	vector<int>a(k);
    vector<bool>w(n);
	for(int i=0;i<k;i++) cin>>a[i], a[i]--, w[a[i]] = 1;
    vector<int>x(n), y(n);
	for(int i=0;i<n;i++) cin>>x[i]>>y[i];
    auto get_dist = [&](int i, int j)->lint {
		return lint(x[i] - x[j])*(x[i] - x[j]) + lint(y[i] - y[j])*(y[i] - y[j]);
	};
	lint ans = 0;
	for(int i=0;i<n;i++){
		if(w[i]) continue;
		lint cur = lint(1e18);
		for(int j=0;j<n;j++){
			if(!w[j]) continue;
			cur = min(cur, get_dist(i, j));
		}
		ans = max(ans, cur);
	}
	cout<<fixed<<setprecision(8);
	cout<<sqrtl(double(ans))<<"\n";
    
}