#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int lim = 1<<18;
const int lg = 60;
const int lim2 = 1<<17;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, c; lint k;
    cin>>n>>c>>k;
    vector<vector<lint>>val(c);
    vector<int>f(c);
    for(int i=0;i<n;i++){
        lint d, v;
        cin>>d>>v;
        d--;
        val[d].push_back(v);
        f[d]++;
    }
    vector<lint>a = {0}, b = {0};

    {
        vector<pair<int, int>>aux(c);
        for(int i=0;i<c;i++){
            aux[i] = {f[i], i};
        }
        sort(aux.rbegin(), aux.rend());

        int sza = 1, szb = 1;
        a.reserve(lim2), b.reserve(lim);
        lint cuma = 0, cumb = 0;
        for(auto [fi, i] : aux){
            if(szb * fi > lim){
                a.resize(sza * fi);
                for(int j=1;j<fi;j++){
                    for(int l=0;l<sza;l++){
                        a[j*sza + l] = a[l] ^ val[i][j] ^ val[i][0];
                    }
                }
                cuma ^= val[i][0];
                sza *= fi;    
            }
            else{
                b.resize(szb * fi);
                for(int j=1;j<fi;j++){
                    for(int l=0;l<szb;l++){
                        b[j*szb + l] = b[l] ^ val[i][j] ^ val[i][0];
                    }
                }
                cumb ^= val[i][0];
                szb *= fi;    
            }
        }
        for(lint& u : a) u ^= cuma;
        for(lint& u : b) u ^= cumb;
    }

    vector<array<int, 2>>trie(1, {-1, -1});
    vector<int>sz(1);
    trie.reserve(60 * b.size());
    sz.reserve(60 * b.size());

    for(lint u : b){
        int cur = 0;
        for(int i=lg-1;i>=0;i--){
            int x = u>>i&1;
            if(trie[cur][x] == -1){
                trie[cur][x] = trie.size();
                trie.push_back({-1, -1});
                sz.push_back(0);
            }
            cur = trie[cur][x];
            sz[cur]++;
        }
    }


    int sa = int(a.size()), sb = int(b.size());
    vector<int>state(a.size());
    lint cnt = 0, ans = 0;
    for(int j=lg-1;j>=0;j--){
        lint cur = 0;
        for(int i=0;i<sa;i++){
            if(state[i] == -1) continue;
            int x = a[i]>>j&1;
            if(trie[state[i]][x^1] != -1) cur += sz[trie[state[i]][x^1]];
        }
        if(cnt + cur >= k){
            ans |= 1ll<<j;
            for(int i=0;i<sa;i++){
                if(state[i] == -1) continue;
                int x = a[i]>>j&1;
                state[i] = trie[state[i]][x^1];
            }
        }
        else{
            cnt += cur;
            for(int i=0;i<sa;i++){
                if(state[i] == -1) continue;
                int x = a[i]>>j&1;
                state[i] = trie[state[i]][x];
            }
        }
    }
    cout<<ans<<"\n";

    return 0;
}
