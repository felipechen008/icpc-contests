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
        if(n == 1){
            if(a[0] == 1) cout<<"YES\n";
            else cout<<"NO\n";
        }
        else{
            sort(a.rbegin(), a.rend());
            if(a[0] > a[1] + 1) cout<<"NO\n";
            else cout<<"YES\n";
        }
    }
    return 0;
}
