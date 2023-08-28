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
    int n, a, b;
    cin>>n>>a>>b;
    for(int i=0;i<n;i++){
        char c, d;
        cin>>c>>d;
        if(c == 'Y' || !b) cout<<"Y ", a--, b++;
        else cout<<"N ";
        if(d == 'Y' || !a) cout<<"Y", a++, b--;
        else cout<<"N";
        cout<<"\n";
    }
    return 0;
}
