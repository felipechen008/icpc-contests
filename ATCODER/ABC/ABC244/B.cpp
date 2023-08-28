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
    string t;
    cin>>n>>t;
    vector<int>dx = {1, 0, -1, 0};
    vector<int>dy = {0, -1, 0, 1};
    int k = 0;
    int x = 0, y = 0;
    for(char c : t){
        if(c == 'S') x += dx[k], y += dy[k];
        else k = (k + 1) % 4;
    }
    cout<<x<<" "<<y<<"\n";
    return 0;
}
