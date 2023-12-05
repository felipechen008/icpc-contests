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
        int n;
        cin>>n;
        vector<int>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        int mn = inf;
        lint ans = 0;
        for(int i=n-1;i>=0;i--){
            if(a[i] > mn){
                int k = a[i] / mn;
                int r = a[i] % mn;
                ans += k - 1;
                if(r){
                    mn = a[i] / (k + 1);
                    ans++;
                }
            }
            else mn = a[i];
        }
        cout<<ans<<"\n";
    }
    return 0;
}
