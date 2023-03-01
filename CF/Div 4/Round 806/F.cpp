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
        lint ans = 0;
        vector<int>pref(n+1);
        for(int i=0;i<n;i++){
            if(a[i] > i) pref[i+1] = pref[i];
            else{
                if(a[i]) ans += pref[a[i] - 1];
                pref[i+1] = pref[i] + 1;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
