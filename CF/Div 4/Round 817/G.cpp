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
        int odd = 0, even = 0;
        vector<int>a(n);
        for(int i=0;i<n-2;i++){
            a[i] = i;
            if(i&1) odd ^= i;
            else even ^= i;
        }
        int diff = odd ^ even;
        if(!diff){
            if((n-3)&1){
                odd ^= a[n-3];
                a[n-3]++;
                odd ^= a[n-3];
            }
            else{
                even ^= a[n-3];
                a[n-3]++;
                even ^= a[n-3];
            }
            diff = odd ^ even;
        }
        a[n-2] = (1<<20);
        a[n-1] = (1<<20) ^ diff;
        for(int u : a) cout<<u<<" ";
        cout<<"\n";
    }
    return 0;
}
