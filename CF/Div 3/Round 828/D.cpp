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
        int cnt = 0;
        for(int i=0;i<n;i++) while(a[i] % 2 == 0) a[i] /= 2, cnt++;
        vector<int>b(n);
        for(int i=1;i<=n;i++){
            int cur = 0, j = i;
            while(j % 2 == 0) j /= 2, cur++;
            b[i-1] = cur; 
        } 
        sort(b.rbegin(), b.rend());
        int ans = 0;
        for(int i=0;i<n;i++){
            if(cnt >= n) break;
            ans++;
            cnt += b[i];
        }
        if(cnt < n) ans = -1;
        cout<<ans<<"\n";
    }
    return 0;
}
