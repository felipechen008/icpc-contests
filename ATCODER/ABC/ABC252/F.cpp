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
    lint n, l;
    cin>>n>>l;
    vector<lint>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    priority_queue<lint, vector<lint>, greater<lint>>pq;
    lint tot = 0;
    for(int i=0;i<n;i++){
        pq.push(a[i]);
        tot += a[i];
    }
    if(l != tot) pq.push(l - tot);
    lint ans = 0;
    while(pq.size() > 1){
        lint u = pq.top();
        pq.pop();
        lint v = pq.top();
        pq.pop();
        ans += u + v;
        pq.push(u + v);
    }
    cout<<ans<<"\n";

    return 0;
}
