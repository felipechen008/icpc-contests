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
        vector<int>last(1001), a(n);
        for(int i=0;i<n;i++) cin>>a[i], last[a[i]] = i + 1;
        int ans = -1;
        for(int i=1;i<=1000;i++){
            if(!last[i]) continue;
            for(int j=i;j<=1000;j++){
                if(!last[j] || __gcd(i, j) > 1) continue;
                ans = max(ans, last[i] + last[j]);
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
