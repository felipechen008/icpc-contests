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
        string a, b;
        cin>>a>>b;
        for(char& c : a) if(c == 'G') c = 'B';
        for(char& c : b) if(c == 'G') c = 'B';
        if(a == b) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
