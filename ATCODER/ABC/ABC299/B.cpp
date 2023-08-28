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
    int n, t;
    cin>>n>>t;
    vector<int>c(n), r(n);
    for(int i=0;i<n;i++) cin>>c[i];
    for(int i=0;i<n;i++) cin>>r[i];
    int ans = -1, id = -1;
    for(int i=0;i<n;i++){
        if(c[i] == t){
            if(ans < r[i]) ans = r[i], id = i;
        }
    }
    if(ans == -1){
        for(int i=0;i<n;i++){
            if(c[i] == c[0]){
                if(ans < r[i]) ans = r[i], id = i;
            }
        }
    }
    cout<<id + 1<<"\n";

    return 0;
}
