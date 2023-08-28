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
        int n, q;
        cin>>n>>q;
        vector<int>a(n);
        lint sum = 0;
        for(int i=0;i<n;i++) cin>>a[i], sum += a[i];
        array<int, 2>v = {0, 0};
        for(int i=0;i<n;i++) v[a[i]&1]++;
        while(q--){
            int op, x;
            cin>>op>>x;
            sum += lint(1) * x * v[op];
            if(x&1) v[op ^ 1] += v[op], v[op] = 0;
            cout<<sum<<"\n";
        }
    }
    return 0;
}
