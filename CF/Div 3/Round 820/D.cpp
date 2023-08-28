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
        vector<int>x(n), y(n);
        for(int i=0;i<n;i++) cin>>x[i];
        for(int i=0;i<n;i++) cin>>y[i];
        vector<int>ids(n), d(n);
        for(int i=0;i<n;i++) d[i] = y[i] - x[i];
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j){
            return d[i] < d[j];
        });
        int ans = 0;
        for(int l=0,r=n-1;l<r;){
            int i = ids[l], j = ids[r];
            if(d[i] + d[j] >= 0){
                ans++;
                l++, r--;
            }
            else l++;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
