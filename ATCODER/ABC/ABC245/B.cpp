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
    int n;
    cin>>n;
    vector<bool>w(2010);
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i], w[a[i]] = 1;
    for(int i=0;i<=n;i++){
        if(!w[i]){
            cout<<i<<"\n";
            break;
        }
    }
    return 0;
}
