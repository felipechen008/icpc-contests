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
    vector<int>p(n);
    for(int i=1;i<n;i++) cin>>p[i], p[i]--;
    int ans = 0, id = n - 1;
    while(id){
        ans++;
        id = p[id];
    }
    cout<<ans<<"\n";
    return 0;
}
