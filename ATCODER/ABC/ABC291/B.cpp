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
    vector<int>a(5*n);
    for(int i=0;i<5*n;i++) cin>>a[i];
    sort(a.begin(), a.end());
    int cnt = 0;
    for(int i=n;i<4*n;i++) cnt += a[i];
    cout<<fixed<<setprecision(9);
    cout<< (1.0 * cnt) / (3 * n)<<"\n";
    return 0;
}
