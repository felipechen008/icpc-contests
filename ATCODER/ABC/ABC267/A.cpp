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
    vector<string>s = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    string t;
    cin>>t;
    for(int i=0;i<5;i++){
        if(s[i] == t) cout<<5 - i<<"\n";
    }
    return 0;
}
