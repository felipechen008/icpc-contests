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
        string a, b;
        cin>>a>>b;
        int c = 0, d = 0;
        for(char ch : a) c += ch == 'X'; 
        for(char ch : b) d += ch == 'X'; 
        char p = a.back(), q = b.back();
        int ok = 1;
        if(p == 'S'){
            if(q == 'S'){
                if(c < d) ok = 1;
                else if(c > d) ok = -1;
                else ok = 0;
            }
            else ok = -1;
        }
        else if(p == 'M'){
            if(q == 'S') ok = 1;
            else if(q == 'M') ok = 0;
            else ok = -1;
        }
        else{
            if(q == 'L'){
                if(c < d) ok = -1;
                else if(c > d) ok = 1;
                else ok = 0;
            }
            else ok = 1;
        }
        if(ok == 1) cout<<">\n";
        else if(ok == 0) cout<<"=\n";
        else cout<<"<\n";
    }
    return 0;
}
