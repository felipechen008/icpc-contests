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
        for(int i=0;i<n;i++){
            if(a[i]&1) a[i] += a[i] % 10;
            if(a[i] % 10){
                while(a[i] % 10 != 2) a[i] += a[i] % 10;
                a[i] %= 20;
            }
        }
        int cnt = 0;
        for(int i=0;i<n;i++) cnt += a[i] != a[0];
        if(cnt) cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}
