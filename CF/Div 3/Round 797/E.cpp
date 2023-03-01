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
    int t;
    cin>>t;
    while(t--){
        int n, k;
        cin>>n>>k;
        vector<int>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        lint ans = 0;
        vector<int>f(k);
        for(int i=0;i<n;i++) ans += a[i] / k, a[i] = a[i] % k, f[a[i]]++;
        for(int l=1,r=k-1;l<=r;r--){
            while(l <= r && f[r]){
                if(l == r){
                    ans += f[l] / 2;
                    f[l] = 0;
                }
                else{
                    int x = min(f[l], f[r]);
                    f[l] -= x;
                    f[r] -= x;
                    ans += x;
                }
                if(!f[l]) l++;
            }
            if(l + r == k) l++;
        }
        cout<<ans<<"\n";
    }

    return 0;
}
