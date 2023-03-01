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
        vector<int>s(n+1), f(n+1);
        for(int i=0;i<n;i++) cin>>s[i];
        for(int i=0;i<n;i++) cin>>f[i];
        s[n] = f[n] = inf;
        int last = 0;
        vector<int>ans(n);
        for(int l=0,r=0;r<=n;r++){  
            while(f[l] < s[r]) ans[l] = f[l] - last, last = f[l], l++;
            if(l == r) last = s[r];
        }
        for(int u : ans) cout<<u<<" ";
        cout<<"\n";
        
    }
    return 0;
}
