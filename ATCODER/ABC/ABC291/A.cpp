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
    string s;
    cin>>s;
    int n = int(size(s));
    for(int i=0;i<n;i++){
        if(s[i] <= 'Z') cout<<i+1<<"\n";
    }

    return 0;
}
