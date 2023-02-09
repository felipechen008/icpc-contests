#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int B = 18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin>>q;
    vector<int>root(1);
    vector<array<int, 2>>trie(2e7);
    int id = 1;

    while(q--){
        int op;
        cin>>op;
        if(op == 0){
            int x;
            cin>>x;
            int last = root.back();
            root.push_back(id);
            for(int b=B;b>=0;b--){
                int c = x>>b&1;
                trie[id] = trie[last];
                trie[id][c] = id + 1;
                last = trie[last][c];
                id++;
            }
        }
        else if(op == 1){
            int l, r, x;
            cin>>l>>r>>x;
            int y = 0;
            l = root[l-1], r = root[r];
            for(int b=B;b>=0;b--){
                int c = x>>b&1;
                if(trie[l][!c] != trie[r][!c]){
                    l = trie[l][!c], r = trie[r][!c];
                    y |= (!c)<<b;
                }
                else{
                    l = trie[l][c], r = trie[r][c];
                    y |= c<<b;
                }
            }
            cout<<y<<"\n";
        }
        else{
            int k;
            cin>>k;
            for(int i=0;i<k;i++) root.pop_back();
        }
    }


    return 0;
}
