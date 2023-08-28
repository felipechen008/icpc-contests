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
    int n, m;
    cin>>n>>m;
    vector<int>a(n), last(m, -1);
    for(int i=0;i<n;i++) cin>>a[i], a[i]--;
    for(int i=n-1;i>=0;i--){
        if(last[a[i]] == -1) last[a[i]] = i;
    }
    vector<bool>w(m);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>cur;
    vector<int>ans;
    int last_update = -1;
    for(int i=0;i<n;i++){
        if(w[a[i]]) continue;
        cur.push({a[i], i});
        if(last[a[i]] == i){
            while(!cur.empty()){
                auto [b, j] = cur.top();
                if(b > a[i]) break;
                cur.pop();
                if(!w[b] && j > last_update){
                    w[b] = 1;
                    last_update = j;
                    ans.push_back(b);
                }
            }
        }
    }
    for(int u : ans) cout<<u+1<<" ";
    cout<<"\n";

    return 0;
}
