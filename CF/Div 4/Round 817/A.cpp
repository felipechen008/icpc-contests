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
    string a = "Timur";
    sort(a.begin(), a.end());
    while(t--){
        int n;
        string b;
        cin>>n>>b;
        sort(b.begin(), b.end());
        if(a == b) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
