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
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i], a[i]--;
    lint ans = 0, cnt = 0;
    for(int i=0;i<n;i++){
        if(a[i] == i) ans += cnt++;
        else ans += a[a[i]] == i && a[i] < i;
    }
    cout<<ans<<"\n";
    return 0;
}
