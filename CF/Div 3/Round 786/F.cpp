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
    int n, m, q;
    cin>>n>>m>>q;
    vector<string>s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    int cnt = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cnt += s[i][j] == '*';
    }
    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j] == '*' && j*n + i > cnt) ans++;
        }
    }
    while(q--){
        int x, y;
        cin>>x>>y;
        x--, y--;
        if(s[x][y] == '*'){
            s[x][y] = '.';
            if(s[cnt % n][cnt / n] == '*') ans++;
            if(y*n + x > cnt) ans--;
            cnt--;
        }   
        else{
            cnt++;
            if(s[cnt % n][cnt / n] == '*') ans--;
            s[x][y] = '*';
            if(y*n + x > cnt) ans++;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
