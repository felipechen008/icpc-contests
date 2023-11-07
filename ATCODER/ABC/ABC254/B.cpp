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
    vector<vector<int>>ch(n+1, vector<int>(n+1));
    for(int i=0;i<n;i++){
        ch[i][0] = ch[i][i] = 1;
        for(int j=1;j<i;j++) ch[i][j] = ch[i-1][j] + ch[i-1][j-1];
        for(int j=0;j<=i;j++) cout<<ch[i][j]<<" ";
        cout<<"\n"; 
    }


    return 0;
}
