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
    int n, m;
    cin>>n>>m;
    vector<lint>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    lint ans = 0, cnt = 0, sum = 0;
    for(int i=0;i<m;i++) sum += a[i], cnt += a[i] * (i + 1);
    ans = cnt;
    for(int i=m;i<n;i++){
        cnt += -sum + a[i] * m;
        sum += a[i] - a[i-m];
        ans = max(ans, cnt);
    }
    cout<<ans<<"\n";
    return 0;
}
