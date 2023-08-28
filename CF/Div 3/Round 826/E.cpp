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
        vector<int>b(n);
        for(int i=0;i<n;i++) cin>>b[i];
        vector<bool>w(n+1);
        w[0] = 1;
        for(int i=0;i<n;i++){
            if(w[i]){
                if(b[i] < n-i) w[i + b[i] + 1] = 1;
            }
            if(b[i] <= i && w[i - b[i]]) w[i + 1] = 1;
        }
        if(w[n]) cout<<"YES\n";
        else cout<<"NO\n";

    }
    return 0;
}
