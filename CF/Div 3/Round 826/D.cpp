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
        vector<int>p(n);
        for(int i=0;i<n;i++) cin>>p[i], p[i]--;
        int m = __builtin_ctz(n);
        bool ok = true;
        int ans = 0;
        for(int b=m-1;b>=0;b--){
            for(int i=0;i<1<<(m-b);i++){
                int cnt = 0;
                for(int j=0;j<1<<b;j++){
                    int k = i * (1<<b) + j;
                    cnt += p[k] >> b & 1;
                }
                if(cnt){
                    if(cnt != (1<<b)) ok = false;
                    else{
                        if(!(i&1)) ans++;
                    }
                }
            }
        }
        if(ok) cout<<ans<<"\n";
        else cout<<"-1\n";
    }
    return 0;
}
