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
        for(int i=0;i<n;i++) cin>>a[i], a[i]--;
        int l = 0, r = n-1;
        int x = 0, y = n-1;
        while(l <= r){
            if(a[l] == x) l++, x++;
            else if(a[l] == y) l++, y--;
            else if(a[r] == x) r--, x++;
            else if(a[r] == y) r--, y--;
            else break;
        }
        if(l > r) cout<<"-1\n";
        else cout<<l+1<<" "<<r+1<<"\n";
    }
    return 0;
}
