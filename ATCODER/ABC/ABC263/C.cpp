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
    int n, m;
    cin>>n>>m;
    vector<vector<int>>ans;
    vector<int>cur;
    auto gen = [&](auto& self, int x, int y)->void {
        if(y == m){
            if(x == n) ans.push_back(cur);
            return;
        }
        if(x < n){
            cur.push_back(y);
            self(self, x + 1, y + 1);
            cur.pop_back();
        }
        self(self, x, y + 1);
    };
    gen(gen, 0, 0);
    for(auto& v : ans){
        for(int u : v) cout<<u + 1<<" ";
        cout<<"\n";
    }
    return 0;
}
