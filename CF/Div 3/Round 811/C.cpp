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
        int s;
        cin>>s;
        string ans;
        for(int i=9;i>=1;i--){
            if(s > i) ans.push_back('0' + i), s -= i;
            else{
                ans.push_back('0' + s);
                break;
            }
        }
        reverse(ans.begin(), ans.end());
        cout<<ans<<"\n";
    }
    return 0;
}
