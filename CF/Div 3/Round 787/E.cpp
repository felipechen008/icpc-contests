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
        int n, k;
        cin>>n>>k;
        string s;
        cin>>s;
        int ind = -1;
        for(int i=0;i<n;i++){
            if(s[i] - 'a' > k){
                ind = i;
                break;
            }
        }
        if(ind == -1){
            for(int i=0;i<n;i++) cout<<"a";
            cout<<"\n";
        }
        else{
            int mx = 0;
            for(int i=0;i<ind;i++) mx = max(mx, s[i] - 'a');
            int o = s[ind] - 'a';
            int l = k - mx;
            for(int i=0;i<n;i++){
                int c = s[i] - 'a';
                if(c <= mx) s[i] = 'a';
                else if(o - l <= c && c <= o) s[i] = 'a' + o - l;
            }
            cout<<s<<"\n";
        }
    }
    return 0;
}
