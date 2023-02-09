#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

using ld = double;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<int>f;
    ld pot = 100;
    for(int i=0;i<4000;i++){
        f.push_back(int(pot));
        pot *= 1.005;
        if(pot > 5e6) break;
    }
    int n = int(size(f));
    vector<double>p(n, 1.0/n);
    for(int z=0;z<50;z++){
        ld mx = 0;
        int ind = -1;
        for(int i=0;i<n;i++){
            if(p[i] > mx){
                mx = p[i];
                ind = i;
            }
        }
        int c = log(0.5) / log(1.0 - f[ind]/1e7);
        cout<<"test "<<c<<endl;
        ld no = pow(1.0 - f[ind]/1e7, c);
        int x;
        cin>>x;
        if(x){
            for(int i=0;i<n;i++){
                p[i] = (1 - pow(1.0 - f[i]/1e7, c)) * p[i] / (1.0 - no);
            }
        }
        else{
            for(int i=0;i<n;i++){
                p[i] = pow(1.0 - f[i]/1e7, c) * p[i] / no;
            }
        }
    }
    ld mx = 0;
    int ind = -1;
    for(int i=0;i<n;i++){
        if(p[i] > mx){
            mx = p[i];
            ind = i;
        }
    }
    cout<<"estimate "<<f[ind]<<endl;


    return 0;
}
