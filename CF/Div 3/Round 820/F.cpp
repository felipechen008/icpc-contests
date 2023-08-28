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
        string s;
        cin>>s;
        int n = int(size(s));
        int w, q;
        cin>>w>>q;
        vector<int>pref(n+1);
        for(int i=0;i<n;i++){
            pref[i+1] = pref[i] + (s[i] - '0');
        }
        vector<vector<int>>cnt(9);
        for(int i=w;i<=n;i++){
            int v = pref[i] - pref[i-w];
            cnt[v % 9].push_back(i - w + 1);
        }
        while(q--){
            int l, r, k;
            cin>>l>>r>>k;
            int v = (pref[r] - pref[l-1]) % 9;
            int x = inf, y = inf;
            for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                    if( (i * v + j) % 9 == k ){
                        if(i == j){
                            if(size(cnt[i]) >= 2){
                                int a = cnt[i][0], b = cnt[i][1];
                                if( tie(a, b) < tie(x, y) ) x = a, y = b;
                            }
                        }
                        else{
                            if(!cnt[i].empty() && !cnt[j].empty()){
                                int a = cnt[i][0], b = cnt[j][0];
                                if( tie(a, b) < tie(x, y) ) x = a, y = b;
                            }
                        }
                    }
                }
            }
            if(x == inf) x = -1, y = -1;
            cout<<x<<" "<<y<<"\n";
        }
    }
    return 0;
}
