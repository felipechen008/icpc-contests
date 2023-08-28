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
        vector<int>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        string s;
        cin>>s;
        int cnt = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(a[i] == a[j]) cnt += s[i] != s[j];
            }
        }
        if(cnt) cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}
