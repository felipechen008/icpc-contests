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
        int x = 0;
        for(int i=0;i<n;i++) x += a[i] == 2;
        if(x&1){
            cout<<"-1\n";
            continue;
        }
        for(int i=0,j=0;i<n;i++){
            j += a[i] == 2;
            if(j == x / 2){
                cout<<i+1<<"\n";
                break;
            }
        }
    }

    return 0;
}
