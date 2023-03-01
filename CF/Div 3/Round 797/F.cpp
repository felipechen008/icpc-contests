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
        string s;
        cin>>n>>s;
        vector<int>p(n);
        for(int i=0;i<n;i++) cin>>p[i], p[i]--;
        vector<bool>vis(n);
        lint lcm = 1;
        for(int i=0;i<n;i++){
            if(vis[i]) continue;
            vector<int>cur;
            int j = i;
            while(!vis[j]){
                cur.push_back(j);
                vis[j] = 1;
                j = p[j];
            }
            int m = size(cur);
            lint cycle = m;
            for(int d=1;d<m;d++){
                if(m % d) continue;
                int cnt = 0;
                for(int r=0;r<d;r++){
                    int diff = 0;
                    for(int k=r;k<m;k+=d) diff += s[cur[k]] == s[cur[r]];
                    cnt += diff == m/d;
                }
                if(cnt == d){
                    cycle = d;
                    break;
                }
            }
            lint g = __gcd(lcm, cycle);
            lcm = lcm * (cycle / g);
        }
        cout<<lcm<<"\n";
    }
    return 0;
}
