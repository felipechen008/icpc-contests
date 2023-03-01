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
        set<char>q;
        int ans = 0;
        for(int i=0,j=3;i<int(size(s));i++){
            if(!q.count(s[i])) j++;
            if(j == 4) j = 1, ans++, q.clear();
            q.insert(s[i]);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
