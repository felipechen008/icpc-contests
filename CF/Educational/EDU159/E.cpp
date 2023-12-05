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
    vector<string>s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    lint ans = 0;
    for(int i=0;i<n;i++) ans += s[i].size();
    ans = ans * n * 2;
    vector<int>iden(26, -1), f(1);
    vector<vector<int>>trie(1, iden);
    for(int i=0;i<n;i++){
        int cur = 0;
        for(char ch : s[i]){
            int c = ch - 'a';
            if(trie[cur][c] == -1){
                trie[cur][c] = trie.size();
                trie.push_back(iden);
                f.push_back(0);
            }
            cur = trie[cur][c];
            f[cur]++;
        }
    }
    for(int i=0;i<n;i++){
        int sz = (int)s[i].size();
        int cur = 0;
        for(int j=sz-1;j>=0;j--){
            int c = s[i][j] - 'a';
            if(trie[cur][c] == -1) break;
            cur = trie[cur][c];
            ans -= f[cur] * 2;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
