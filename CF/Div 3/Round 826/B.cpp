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
        if(n == 3) cout<<"-1\n";
        else if(n&1){
            for(int i=4;i<=n;i++) cout<<i<<" ";
            cout<<"1 2 3 \n";
        }
        else{
            for(int i=n;i>=1;i--) cout<<i<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
