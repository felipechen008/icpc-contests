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
    lint ans = 0;
    for(int i=1;i<=n;i++){
        int aux = i;
        int c = 1;
        for(int j=2;j*j<=aux;j++){
            if(aux % j == 0){
                int cur = 0;
                while(aux % j == 0) aux /= j, cur++;
                if(cur&1) c *= j;
            }
        }
        if(aux > 1) c *= aux;
        int cur = (n / c);
        ans += sqrt(cur);
    }
    cout<<ans<<"\n";

    return 0;
}
