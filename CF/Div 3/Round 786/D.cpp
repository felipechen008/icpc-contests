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
        vector<int>b = a;
        sort(b.begin(), b.end());
        bool ok = true;
        if(n&1){
            if(a[0] != b[0]) ok = false;
            for(int i=1;i<n;i+=2){
                if(a[i] > a[i+1]) swap(a[i], a[i+1]);
                if(a[i] != b[i] || a[i+1] != b[i+1]){
                    ok = false;
                    break;
                }
            }
        }
        else{
            for(int i=0;i<n;i+=2){
                if(a[i] > a[i+1]) swap(a[i], a[i+1]);
                if(a[i] != b[i] || a[i+1] != b[i+1]){
                    ok = false;
                    break;
                }
            }
        }
        if(ok) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
