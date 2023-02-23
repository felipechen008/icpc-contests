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
        string s;
        cin>>s;
        
        for(int i=0,k=1;i<26;i++){
            for(int j=0;j<26;j++){
                if(i == j) continue;
                if(s[0] - 'a' == i && s[1] - 'a' == j) cout<<k<<"\n";
                k++;
            }
        }
    }
    return 0;
}
