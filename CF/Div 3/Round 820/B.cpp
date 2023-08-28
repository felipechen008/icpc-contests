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
        string s;
        cin>>s;
        string ans;
        for(int i=n-1;i>=0;i--){
            if(s[i] == '0'){
                int c = (s[i-2] - '0') * 10 + (s[i-1] - '0') - 1;
                ans.push_back('a' + c);
                i -= 2;
            }
            else{
                int c = s[i] - '0' - 1;
                ans.push_back('a' + c);
            }
        }
        reverse(ans.begin(), ans.end());
        cout<<ans<<"\n";
    }
    return 0;
}
