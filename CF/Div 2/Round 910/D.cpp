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
        vector<lint>a(n), b(n);
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<n;i++) cin>>b[i];
        lint cur = 0;
        for(int i=0;i<n;i++) cur += abs(a[i] - b[i]);
        lint pos = -linf, neg = -linf;
        for(int i=0;i<n;i++){
            pos = max(pos, -abs(a[i] - b[i]) + a[i] + b[i]);
            neg = max(neg, -abs(a[i] - b[i]) - a[i] - b[i]);
        }
        cout<<cur + max(0ll, pos + neg)<<"\n";
    }
    return 0;
}
