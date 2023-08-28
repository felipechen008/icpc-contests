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
        int a, b, c, d;
        cin>>a>>b>>c>>d;
        vector<int>diva, divb;
        for(int i=1;i*i<=a;i++){
            if(a % i == 0){
                diva.push_back(i);
                if(i != a / i) diva.push_back(a/i);
            }
        }
        for(int i=1;i*i<=b;i++){
            if(b % i == 0){
                divb.push_back(i);
                if(i != b / i) divb.push_back(b/i);
            }
        }
        int x = -1, y = -1;
        for(int u : diva){
            for(int v : divb){
                int lx = a / u + 1, rx = c / u;
                int ly = b / v + 1, ry = d / v;
                int aa = a / u, bb = b / v;
                lx = (lx + bb - 1) / bb;
                rx = rx / bb;
                ly = (ly + aa - 1) / aa;
                ry = ry / aa;
                if(lx <= rx && ly <= ry){
                    x = lx * bb * u;
                    y = ly * aa * v;
                }
            }
            if(x != -1) break;
        }
        cout<<x<<" "<<y<<"\n";
        
    }
    return 0;
}
