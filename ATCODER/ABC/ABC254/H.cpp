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
    vector<int>a(n), b(n);
    map<int, int>f, g;
    for(int i=0;i<n;i++) cin>>a[i], f[a[i]]++;
    for(int i=0;i<n;i++) cin>>b[i], g[b[i]]++;
    int ans = 0;
    while(!f.empty()){
        auto [x, y] = *f.rbegin();
        auto [z, w] = *g.rbegin();
        if(x == z){
            int k = min(y, w);
            f.rbegin()->nd -= k;
            g.rbegin()->nd -= k;
            if(!f.rbegin()->nd) f.erase(x);
            if(!g.rbegin()->nd) g.erase(z);
        }
        else if( x < z ){
            if(z&1){
                cout<<"-1\n";
                return 0;
            }
            ans += w;
            g[z / 2] += w;
            g.erase(z);
        }
        else{
            f[x / 2] += y;
            ans += y;
            f.erase(x); 
        }
    }
    cout<<ans<<"\n";

    return 0;
}
