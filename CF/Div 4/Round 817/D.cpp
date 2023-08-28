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
        vector<int>a(n);
        lint ans = 0;
        for(int i=0;i<n;i++){
            if(s[i] == 'L') a[i] = (n - 1 - i) - i, ans += i;
            else a[i] = i - (n - 1 - i), ans += n - 1 - i;
        }
        sort(a.rbegin(), a.rend());
        for(int i=0;i<n;i++){
            ans += max(a[i], 0);
            cout<<ans<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
