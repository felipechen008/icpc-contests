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
        vector<int>a(n), b(n);
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<n;i++) cin>>b[i];
        int mx = inf;
        bool ok = true;
        for(int i=0;i<n;i++){
            if(!b[i]) continue;
            if(b[i] > a[i] || (mx != inf && a[i] - b[i] != mx)){
                ok = false;
                break;
            }
            if(mx == inf) mx = a[i] - b[i];
        }
        for(int i=0;i<n;i++){
            if(!b[i] && a[i] > mx){
                ok = false;
                break;
            }
        }
        if(ok) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
