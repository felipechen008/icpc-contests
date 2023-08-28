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
        vector<bool>w(n);
        int pref = 0, tot = (1<<30) - 1;
        for(int b=0;b<30;b++){
            int ind = -1, mx = 0;
            for(int i=0;i<n;i++){
                int cur = a[i]&(tot ^ pref);
                if(cur > mx) mx = cur, ind = i;
            }
            if(ind == -1) break;
            cout<<a[ind]<<" ";
            pref |= a[ind];
            w[ind] = 1;
        }
        for(int i=0;i<n;i++) if(!w[i]) cout<<a[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
