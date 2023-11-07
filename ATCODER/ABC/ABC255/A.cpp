#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main(){
	int r, c;
	cin>>r>>c;
	r--, c--;
	vector<vector<int>>a(2, vector<int>(2));
	cin>>a[0][0]>>a[0][1];
	cin>>a[1][0]>>a[1][1];
	
	cout<<a[r][c]<<"\n";
}