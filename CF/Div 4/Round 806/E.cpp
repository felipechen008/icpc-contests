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
        vector<string>s(n);
        for(int i=0;i<n;i++) cin>>s[i];
        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                
                int cnt = 0;
                cnt += s[i][j] == '1';
                cnt += s[n-1-j][i] == '1';
                cnt += s[j][n-1-i] == '1';
                cnt += s[n-1-i][n-1-j] == '1';
                ans += min(cnt, 4 - cnt);
            }
        }
        cout<<ans/4<<"\n";
    }

    return 0;
}
