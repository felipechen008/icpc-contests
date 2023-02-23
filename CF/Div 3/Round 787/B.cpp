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
        int ans = 0;
        for(int i=n-2;i>=0;i--){
            while(a[i] && a[i] >= a[i+1]) ans++, a[i] /= 2;
        }
        if(n > 1 && a[0] == a[1]) cout<<"-1\n";
        else cout<<ans<<"\n";
    }
    return 0;
}
