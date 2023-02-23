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
        vector<int>p(n), d(n);
        for(int i=0;i<n;i++){
            cin>>p[i];
            p[i]--;
            if(p[i] != i) d[p[i]]++;
        }
        vector<bool>vis(n);
        vector<vector<int>>ans;
        for(int i=0;i<n;i++){
            if(!d[i]){
                int j = i;
                vector<int>cur;
                while(!vis[j]){
                    cur.push_back(j);
                    vis[j] = 1;
                    j = p[j];
                }
                reverse(cur.begin(), cur.end());
                ans.push_back(cur);
            }
        }
        cout<<size(ans)<<"\n";
        for(auto& v : ans){
            cout<<size(v)<<"\n";
            for(int u : v) cout<<u+1<<" ";
            cout<<"\n";
        }
        cout<<"\n";
    }

    return 0;
}
