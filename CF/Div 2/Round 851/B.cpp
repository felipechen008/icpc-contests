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
        if(n&1){
            int x = n/2, y = n/2 + 1;
            for(int i=0,p=1;i<10;i++, p *= 10){
                int z = x / p;
                if(z % 10 == 9){
                    if(i&1) x -= 5 * p, y += 5 * p;
                    else x -= 4 * p, y += 4 * p;
                }
                else break;
            }
            if(x % 10 == 9) x -= 4, y += 4;
            cout<<x<<" "<<y<<"\n";
        }
        else cout<<n/2<<" "<<n/2<<"\n";
    }
    return 0;
}
