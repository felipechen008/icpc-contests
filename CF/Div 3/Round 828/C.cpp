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
        char c;
        string s;
        cin>>n>>c>>s;
        s += s;
        int last = -1;
        int ans = -1;
        for(int i=n+n-1;i>=0;i--){
            if(s[i] == 'g') last = i;
            if(i < n && s[i] == c) ans = max(ans, last - i);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
