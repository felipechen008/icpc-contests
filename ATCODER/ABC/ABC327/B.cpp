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
    lint b;
    cin>>b;
    for(lint i=1;i<=20;i++){
        lint cur = 1;
        for(int j=0;j<i;j++){
            if(cur > b / i) cur = linf;
            cur *= i;
        }
        if(cur == b){
            cout<<i<<"\n";
            return 0;
        }
    }
    cout<<"-1\n";
    return 0;
}
