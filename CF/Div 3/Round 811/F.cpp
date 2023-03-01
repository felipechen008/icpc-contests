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
        int n, a, b, c;
        cin>>n>>a>>b>>c;
        int d = (a + b + c);
        if(d&1){
            cout<<"NO\n";
            continue;
        }
        d /= 2;
        int e = d - b, f = d - c, g = d - a;
        if(e + f + g + 1 > n || e < 0 || f < 0 || g < 0){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        int num = 4;
        int middle = 4;
        if(!e) middle = 1;
        if(!f) middle = 2;
        if(!g) middle = 3;
        if(middle == 4) num++;
        int last = middle;
        for(int i=1;i<e;i++){
            cout<<last<<" "<<num<<"\n";
            last = num++;
        }
        if(e) cout<<last<<" "<<1<<"\n", last = 1;
        last = middle;
        for(int i=1;i<f;i++){
            cout<<last<<" "<<num<<"\n";
            last = num++;
        }
        if(f) cout<<last<<" "<<2<<"\n", last = 2;
        last = middle;
        for(int i=1;i<g;i++){
            cout<<last<<" "<<num<<"\n";
            last = num++;
        }
        if(g) cout<<last<<" "<<3<<"\n", last = 3;
        for(int i=num;i<=n;i++){
            cout<<last<<" "<<num<<"\n";
            last = num++;
        }
    }
    return 0;
}
