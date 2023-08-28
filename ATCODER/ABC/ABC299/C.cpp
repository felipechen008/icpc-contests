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
    string s;
    cin>>n>>s;
    int last = -1;
    int ans = 0;
    for(int i=0;i<n;i++){
        if(s[i] == '-'){
            ans = max(ans, i - last - 1);
            last = i;
        }
    }
    if(last != -1){
        ans = max(ans, n - last - 1);
    }
    if(!ans) ans = -1;
    cout<<ans<<"\n";

    return 0;
}
