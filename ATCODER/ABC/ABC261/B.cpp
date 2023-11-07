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
    int n;
    cin>>n;
    vector<string>s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(s[i][j] == 'L') ans += s[j][i] != 'W';
            if(s[i][j] == 'W') ans += s[j][i] != 'L'; 
            if(s[i][j] == 'D') ans += s[j][i] != 'D'; 
        }
    }
    if(ans) cout<<"incorrect\n";
    else cout<<"correct\n";
    return 0;
}
