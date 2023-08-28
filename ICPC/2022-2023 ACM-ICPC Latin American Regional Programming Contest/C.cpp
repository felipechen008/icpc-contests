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
    lint n, p, h;
    cin>>n>>p>>h;
    p--, h--;
    vector<bool>w(n);
    for(int i=n-1;i>=0;i--){
        if(h >= (1ll<<i)) h = (1ll<<(i+1)) - 1 - h, w[i] = 1;
    }
    for(int i=0;i<n;i++){
        if(p >= (1ll<<(n-1-i))){
            if(w[i]){
                p = (1ll<<(n-i)) - 1 - p;
                cout<<"R";
            }
            else{
                p -= (1ll<<(n-1-i));
                cout<<"L";
            }
        }
        else{
            if(w[i]){
                p = (1ll<<(n-1-i)) - 1 - p;
                cout<<"L";
            }
            else{
                cout<<"R";
            }
        }
    }
    cout<<"\n";
    return 0;
}
