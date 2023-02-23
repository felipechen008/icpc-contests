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
        int ans = 0, l = 0, r = 0, cnt = 0, fi = -1, idfi = -1, sig = 0;
        for(int i=0,j=-1;i<n;i++){
            if(!a[i]) j = i, cnt = 0, fi = -1, sig = 0;
            if(a[i] == 2 || a[i] == -2) cnt++;
            if(a[i] < 0){
                if(fi == -1) fi = cnt, idfi = i;
                sig ^= 1;
            }
            if(sig){
                if(ans < cnt - fi) ans = cnt - fi, l = idfi + 1, r = i + 1;
            }
            else{
                if(ans < cnt) ans = cnt, l = j + 1, r = i + 1;
            }
        }
        cout<<l<<" "<<n-r<<"\n";
    }
    return 0;
}
