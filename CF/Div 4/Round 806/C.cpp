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
        vector<int>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<n;i++){
            int m;
            string s;
            cin>>m>>s;
            for(char c : s){
                if(c == 'U') a[i] = (a[i] + 9) % 10;
                else a[i] = (a[i] + 1) % 10;
            }
        }
        for(int u : a) cout<<u<<" ";
        cout<<"\n";
    }
    return 0;
}
