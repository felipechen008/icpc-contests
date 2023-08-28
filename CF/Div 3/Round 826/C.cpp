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
        int sum = 0;
        for(int i=0;i<n;i++) cin>>a[i], sum += a[i];
        int ans = n;
        for(int i=1;i<=n;i++){
            if(sum % i) continue;
            int cnt = sum / i, cur = 0;
            bool ok = true;
            int mx = 0;
            for(int j=0,k=0;j<n;j++){
                cur += a[j];
                if(cur > cnt){
                    ok = false;
                    break;
                }
                if(cur == cnt){
                    cur = 0;
                    mx = max(mx, j - k + 1);
                    k = j + 1;
                }
            }
            if(ok) ans = min(ans, mx);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
