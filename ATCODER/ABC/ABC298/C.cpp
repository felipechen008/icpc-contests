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
    int n, q;
    cin>>n>>q;
    vector<map<int, int>>a(n);
    vector<set<int>>s(200100);
    while(q--){
        int op, i, j;
        cin>>op>>i;
        i--;
        if(op == 1){
            cin>>j;
            j--;
            a[j][i]++;
            s[i].insert(j);
        }
        else if(op == 2){
            for(auto p : a[i]){
                for(int k=0;k<p.nd;k++) cout<<p.st + 1<<" ";
            }
            cout<<"\n";
        }
        else{
            for(int u : s[i]) cout<<u + 1<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
