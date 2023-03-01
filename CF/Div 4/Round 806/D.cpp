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
        set<string>s;
        vector<string>a(n);
        for(int i=0;i<n;i++) cin>>a[i], s.insert(a[i]);
        for(auto& b : a){
            int m = int(size(b));
            bool ok = false;
            for(int i=1;i<m;i++){
                string c = b.substr(0, i);
                string d = b.substr(i, m-i);
                if(s.count(c) && s.count(d)) ok = true;
            }
            if(ok) cout<<"1";
            else cout<<"0";
        }
        cout<<"\n";
    }
    return 0;
}
