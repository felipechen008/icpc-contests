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
        if(n&1){
            cout<<"Yes\n";
            if(n == 1) cout<<"1 2\n";
            else{
                for(int i=(n+1)/2, j=n+1;i;i--,j+=2){
                    cout<<i<<" "<<j<<"\n";
                }
                for(int i=n,j=n+2;j<2*n;i--,j+=2){
                    cout<<i<<" "<<j<<"\n";
                }
            }
        }
        else cout<<"No\n";
    }

    return 0;
}
