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
    int s, t, m;
    cin>>s>>t>>m;
    vector<vector<int>>g(s);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b - s);
    }
    vector<vector<int>>id(t, vector<int>(t, -1));
    for(int i=0;i<s;i++){
        int sz = int(g[i].size());
        for(int j=0;j<sz;j++){
            for(int k=0;k<j;k++){
                int a = g[i][j], b = g[i][k];
                if(a > b) swap(a, b);
                if(id[a][b] == -1) id[a][b] = i;
                else{
                    cout<<id[a][b]+1<<" "<<i+1<<" "<<a+s+1<<" "<<b+s+1<<"\n";
                    return 0;
                }
            }
        }
    }
    cout<<"-1\n";
    return 0;
}
