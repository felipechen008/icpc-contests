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
        int n, m;
        cin>>n>>m;
        string s;
        cin>>s;
        int b = 0;
        for(char c : s) if(c == 'B') b++;
        if(b == m) cout<<"0\n";
        else{
            cout<<"1\n";
            if(b < m){
                int c = 0;
                for(int i=0;i<n;i++) if(s[i] == 'A'){
                    c++;
                    if(c == m - b){
                        cout<<i+1<<" B\n";
                    }
                }
            }
            else{
                int c = 0;
                for(int i=0;i<n;i++) if(s[i] == 'B'){
                    c++;
                    if(c == b - m){
                        cout<<i+1<<" A\n";
                    }
                }
            }
        }
    }
    return 0;
}
