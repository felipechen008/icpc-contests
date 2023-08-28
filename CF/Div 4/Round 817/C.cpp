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
        vector<string>a(n), b(n), c(n);
        map<string, int>f;
        for(int i=0;i<n;i++) cin>>a[i], f[a[i]]++;
        for(int i=0;i<n;i++) cin>>b[i], f[b[i]]++;
        for(int i=0;i<n;i++) cin>>c[i], f[c[i]]++;
        int x = 0, y = 0, z = 0;
        for(int i=0;i<n;i++){
            int val = f[a[i]];
            if(val == 1) x += 3;
            if(val == 2) x += 1;
        }
        for(int i=0;i<n;i++){
            int val = f[b[i]];
            if(val == 1) y += 3;
            if(val == 2) y += 1;
        }
        for(int i=0;i<n;i++){
            int val = f[c[i]];
            if(val == 1) z += 3;
            if(val == 2) z += 1;
        }
        cout<<x<<" "<<y<<" "<<z<<"\n"; 
    }
    return 0;
}
