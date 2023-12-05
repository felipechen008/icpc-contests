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
        int n, m, k;
        cin>>n>>m>>k;
        int d = n + m - 2;
        if( (k - d) % 2 || d > k) cout<<"No\n";
        else{
            cout<<"Yes\n";
            vector<vector<int>>a(n, vector<int>(m-1, 0));
            vector<vector<int>>b(n-1, vector<int>(m, 1));
            int c = (k - d) % 4 == 2;
            for(int i=1;i<m-1;i++){
                a[0][i] = (i&1) ^ c;
            }
            for(int i=0;i<n-1;i++){
                b[i][m-1] = ((m-1)&1) ^ (i&1) ^ c;
            }
            if( (k - d) % 4 == 0 ){

            }

            for(auto v : a){
                for(int u : v){
                    if(u) cout<<"R ";
                    else cout<<"B ";
                }
                cout<<"\n";
            }
            for(auto v : b){
                for(int u : v){
                    if(u) cout<<"R ";
                    else cout<<"B ";
                }
                cout<<"\n";
            }
        }
    }
    return 0;
}
