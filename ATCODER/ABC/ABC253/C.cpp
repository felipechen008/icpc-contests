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
    int q;
    cin>>q;
    map<int, int>f;
    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int x;
            cin>>x;
            f[x]++;
        }
        else if(op == 2){
            int x, c;
            cin>>x>>c;
            f[x] -= c;
            if(f[x] <= 0) f.erase(x);
        }
        else{
            cout<< f.rbegin()->st - f.begin()->st <<"\n";
        }
    }
    return 0;
}
