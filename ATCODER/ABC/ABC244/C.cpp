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
    vector<bool>w(n+n+1);
    cout<<"1"<<endl;
    w[0] = 1;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        x--;
        w[x] = 1;
        for(int j=0;j<n+n+1;j++){
            if(!w[j]){
                cout<<j+1<<endl;
                w[j] = 1;
                break;
            }
        }
    }
    return 0;
}
