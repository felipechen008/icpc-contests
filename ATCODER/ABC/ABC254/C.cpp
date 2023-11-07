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
    int n, k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<vector<int>>b(k);
    for(int i=0;i<n;i++) b[i % k].push_back(a[i]);
    for(auto& v : b) sort(v.begin(), v.end());
    sort(a.begin(), a.end());
    vector<int>c(n);
    for(int i=0,l=0;i<n;l++){
        for(int j=0;j<k && i < n;j++, i++){
            c[i] = b[j][l];
        }
    }
    if(a == c) cout<<"Yes\n";
    else cout<<"No\n";


    return 0;
}
