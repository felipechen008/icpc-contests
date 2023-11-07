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
	int n;
	cin>>n;
	vector<int>a(n), b(n);
	for(int i=0;i<n;i++) cin>>a[i], a[i]--;
	for(int i=0;i<n;i++) cin>>b[i], b[i]--;
	if(a[0]){
		cout<<"-1\n";
		return 0;
	}
	int lastl = -1, lastr = -1;
	vector<int>v, left(n, -1), right(n, -1);
	for(int l=0,r=0;l<n;l++){
		if(lastr != -1) right[lastr] = a[l];
		if(lastl != -1) left[lastl] = a[l];
		v.push_back(a[l]);
		lastl = a[l], lastr = -1;
		while(!v.empty() && v.back() == b[r]){
			v.pop_back();
			lastl = -1, lastr = b[r++];
		}
	}
    if(!v.empty()){
        cout<<"-1\n";
        return 0;
    }
	for(int i=0;i<n;i++) cout<<left[i] + 1<<" "<<right[i] + 1<<"\n";
    return 0;
}
