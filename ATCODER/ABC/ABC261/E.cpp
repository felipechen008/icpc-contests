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
    int n, c;
    cin>>n>>c;
    vector<int>t(n), a(n);
    for(int i=0;i<n;i++) cin>>t[i]>>a[i];
    vector<vector<int>>v(n + 1, vector<int>(2));
    v[0] = {0, (1<<30) - 1};
    for(int i=0;i<n;i++){
        if(t[i] == 1){
            v[i+1][0] = v[i][0] & a[i];
            v[i+1][1] = v[i][1] & a[i];
        }
        else if(t[i] == 2){
            v[i+1][0] = v[i][0] | a[i];
            v[i+1][1] = v[i][1] | a[i];
        }
        else{
            v[i+1][0] = v[i][0] ^ a[i];
            v[i+1][1] = v[i][1] ^ a[i];
        }
    }
    int cur = c;
    for(int i=1;i<=n;i++){
        int nxt = 0;
        for(int b=0;b<30;b++){
            if(cur>>b&1) nxt |= v[i][1]&(1<<b);
            else nxt |= v[i][0]&(1<<b);
        }
        cur = nxt;
        cout<<cur<<"\n";
    }
    return 0;
}
