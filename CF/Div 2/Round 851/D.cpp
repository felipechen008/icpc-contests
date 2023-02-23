#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 1e9 + 7;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<lint>p2(n+1);
    p2[0] = 1;
    for(int i=0;i<n;i++) p2[i+1] = p2[i] * 2 % mod;

    lint ans = 0;
    for(int i=0;i<n;i++){
        for(int l=i-1,j=i+1,r=i+1;j<n;j++){
            while(l >= 0 && a[i] - a[l] <= a[j] - a[i]) l--;
            while(r < n && a[r] - a[j] < a[j] - a[i]) r++;
            ans += p2[n-r] * p2[l+1] % mod;
            ans %= mod;
        }
    }
    cout<<ans<<"\n";


    return 0;
}
