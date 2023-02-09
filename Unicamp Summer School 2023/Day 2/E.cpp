#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

struct FT{
    vector<int>s;
    FT(int n): s(n){}
    void update(int pos, int diff){
        for(;pos<int(size(s));pos|=pos+1) s[pos] += diff;
    }
    int query(int pos){
        int res = 0;
        for(;pos;pos&=pos-1) res += s[pos-1];
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<array<int, 3>>a(n);
    for(int i=0;i<n;i++){
        int x, y;
        char c;
        cin>>x>>y>>c;
        x *= 2;
        int nx = (x + y);
        int ny = (y - x);
        int z = 0;
        if(c == 'P') z = 1;
        else if(c == 'N') z = -1;
        a[i] = {nx, ny, z};
    }
    vector<int>valx(n), valy(n);
    for(int i=0;i<n;i++) valx[i] = a[i][0];
    for(int i=0;i<n;i++) valy[i] = a[i][1];
    sort(valx.begin(), valx.end());
    valx.erase(unique(valx.begin(), valx.end()), valx.end());
    sort(valy.begin(), valy.end());
    valy.erase(unique(valy.begin(), valy.end()), valy.end());
    for(auto& [x, y, z] : a){
        x = int(lower_bound(valx.begin(), valx.end(), x) - valx.begin());
        y = int(lower_bound(valy.begin(), valy.end(), y) - valy.begin());
    }
    sort(a.begin(), a.end());

    FT seg(n);

    for(auto& [x, y, z] : a){
        if(z == -1) seg.update(y, 1);
        else if(z == 0){
            if(seg.query(y+1)) z = -1;
        }
        else{
            if(seg.query(y+1)){
                cout<<"impossible\n";
                return 0;
            }
        }
    }
    
    reverse(a.begin(), a.end());

    int save = -1, last = -1;
    int ans = 0;

    for(auto& [x, y, z] : a){
        if(z == -1) continue;
        save = max(save, y);
        if(z == 1 && last < y){
            last = save;
            ans++;
        }
    }
    cout<<ans<<"\n";

    return 0;
}
