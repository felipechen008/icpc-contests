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
        sort(a.begin(), a.end());
        if(n == 1){
            cout<<"1\n";
            continue;
        }
        int g = a[1] - a[0];
        for(int i=2;i<n;i++) g = gcd(g, a[i] - a[i-1]);
        lint ans = 0;
        for(int i=0;i<n;i++) ans += (a[n-1] - a[i]) / g;
        int cnt = n;
        for(int i=n-2;i>=0;i--){
            if( (a[n-1] - a[i]) != lint(n-1-i) * g ){
                cnt = (n-1-i);
                break;
            }
        }
        ans += cnt;
        cout<<ans<<"\n";
    }
    return 0;
}
