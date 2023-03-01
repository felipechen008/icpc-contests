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
        int n, H, M;
        cin>>n>>H>>M;
        vector<int>a(n);
        for(int i=0;i<n;i++){
            int h, m;
            cin>>h>>m;
            a[i] = h * 60 + m;
        }
        int A = H * 60 + M;
        int ans = 1440;
        for(int i=0;i<n;i++){
            if(a[i] >= A) ans = min(ans, a[i] - A);
            else ans = min(ans, a[i] + 1440 - A);
        }
        cout<<ans/60<<" "<<ans%60<<"\n";
    }
    return 0;
}
