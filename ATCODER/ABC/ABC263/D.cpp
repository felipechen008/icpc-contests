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
    int n, l, r;
    cin>>n>>l>>r;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<lint>lo(n + 1), hi(n + 1);
    for(int i=0;i<n;i++) lo[i+1] = lo[i] + l - a[i];
    for(int i=n-1;i>=0;i--) hi[i] = hi[i+1] + r - a[i];
    vector<lint>left(n + 1), right(n + 1);
    for(int i=0;i<n;i++) left[i+1] = min(left[i], lo[i]);
    for(int i=n-1;i>=0;i--) right[i] = min(right[i+1], hi[i]);
    lint ans = 0;
    for(int i=0;i<n;i++) ans += a[i];
    lint cnt = 0;
    for(int i=0;i<=n;i++) cnt = min(cnt, lo[i] + right[i]);
    cout<<ans + cnt<<"\n"; 
    return 0;
}
