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
    vector<string>s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    vector<int>d1(n, inf), d2(n, inf);
    {
        d1[0] = 0;
        queue<int>q; q.push(0);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int i=0;i<m;i++){
                if(s[u][i] == '1'){
                    int v = u + i + 1;
                    if(d1[v] == inf){
                        d1[v] = d1[u] + 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    {
        d2[n-1] = 0;
        queue<int>q; q.push(n-1);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int i=0;i<m;i++){
                if(u-i-1 >= 0 && s[u-i-1][i] == '1'){
                    int v = u - i - 1;
                    if(d2[v] == inf){
                        d2[v] = d2[u] + 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    for(int i=1;i<n-1;i++){
        int ans = inf;
        for(int j=1;j<m;j++){
            if(i - j < 0) continue;
            for(int k=j;k<m;k++){
                if(s[i-j][k] == '1') ans = min(ans, d1[i-j] + 1 + d2[i-j+k+1]);
            }
        }
        if(ans == inf) ans = -1;
        cout<<ans<<" ";
    }
    cout<<"\n";
    return 0;
}
