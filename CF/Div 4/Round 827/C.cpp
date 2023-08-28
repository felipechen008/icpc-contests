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
        vector<string>s(8);
        for(int i=0;i<8;i++) cin>>s[i];
        bool red = true;
        for(int i=0;i<8;i++){
            int c = 0;
            for(int j=0;j<8;j++) c += s[j][i] == 'B';   
            if(c == 8) red = false;
        }
        if(red) cout<<"R\n";
        else cout<<"B\n";
    }
    return 0;
}
