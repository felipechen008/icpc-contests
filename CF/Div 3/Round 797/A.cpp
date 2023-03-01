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
        int k = n / 3;
        int r = n % 3;
        int a = k, b = k + 1, c = k - 1;
        if(r >= 1) b++;
        if(r >= 2) a++;
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    return 0;
}
