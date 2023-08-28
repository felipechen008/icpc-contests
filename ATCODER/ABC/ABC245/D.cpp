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
    int n, m;
    cin>>n>>m;
    vector<lint>a(n+1), b(m+1), c(n+m+1);
    for(int i=0;i<=n;i++) cin>>a[i];
    for(int i=0;i<=n+m;i++) cin>>c[i];

    for(int i=n+m;i>=n;i--){
        lint cur = c[i];
        for(int j=0;j<n;j++){
            if(i-j > m) continue; 
            cur -= b[i-j] * a[j];
        }
        b[i-n] = cur / a[n];
    }
    for(lint u : b) cout<<u<<" ";
    cout<<"\n";
    return 0;
}
