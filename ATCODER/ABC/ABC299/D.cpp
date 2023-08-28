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
    int l = 2, r = n-1;
    while(l <= r){
        int mid = (l + r) / 2;
        cout<<"? "<<mid<<endl;
        int x;
        cin>>x;
        if(x) r = mid - 1;
        else l = mid + 1;
    }
    cout<<"! "<<r<<endl;
    return 0;
}
