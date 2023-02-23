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
        string a, b;
        cin>>a>>b;
        if(b == "a") cout<<"1\n";
        else{
            int cnt = 0;
            for(char ch : b) cnt += ch == 'a';
            int n = size(a);
            if(cnt) cout<<"-1\n";
            else cout<<(1ll<<n)<<"\n";
        }
    }
    return 0;
}
