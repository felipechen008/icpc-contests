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
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int>b = a;
    sort(b.begin(), b.end());
    int ans = (b[0] + 1)/2 + (b[1] + 1)/2;
    for(int i=1;i<n;i++){
        if(i > 1){
            int mn = min(a[i-2], a[i]);
            int cur = mn + (a[i-2] - mn + 1)/2 + (a[i] - mn + 1)/2;
            ans = min(ans, cur); 
        }
        if(a[i-1] >= 2 * a[i]){
            ans = min(ans, (a[i-1] + 1)/2);
        }
        else if(a[i] >= 2 * a[i-1]){
            ans = min(ans, (a[i] + 1)/2);
        }
        else{
            ans = min(ans, (a[i-1] + a[i] + 2)/3);
        }
    }
    cout<<ans<<"\n";
    return 0;
}
