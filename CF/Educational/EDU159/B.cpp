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
        lint n, p, l, t;
        cin>>n>>p>>l>>t;
        lint k = n / 7 + (n % 7 != 0);
        lint cnt = p / (t + t + l) + (p % (t + t + l) != 0);
        if(2 * cnt <= k) cout<<n - cnt<<"\n";
        else{
            lint c = (k + 1) / 2;
            p -= k * t + c * l;
            if(p < 0){
                cout<<n - c<<"\n";
            }
            else{
                lint need = p / l + (p % l != 0);
                cout<<n - min(n, c + need)<<"\n";
            }
        }
    }
    return 0;
}
