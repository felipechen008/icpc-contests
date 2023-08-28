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
        string s;
        cin>>n>>s;
        int ans = n-1;
        for(int i=0;i<n-2;i++){
            if(s[i] == s[i+2]) ans--;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
