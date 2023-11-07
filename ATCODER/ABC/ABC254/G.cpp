#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int lg = 20;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q;
    cin>>n>>m>>q;
    vector<array<int, 3>>e(m);
    vector<int>v;
    for(int i=0;i<m;i++){
        int a, b, c;
        cin>>a>>b>>c;
        a--;
        e[i] = {a, b, c};
        v.push_back(b);
        v.push_back(c);
    }
    vector<array<int, 4>>query(q);
    for(int i=0;i<q;i++){
        int x, y, z, w;
        cin>>x>>y>>z>>w;
        x--, z--;
        query[i] = {x, y, z, w};
        v.push_back(y);
        v.push_back(w);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<vector<pair<int, int>>>g(n);
    for(auto& [a, b, c] : e){
        b = int(lower_bound(v.begin(), v.end(), b) - v.begin());
        c = int(lower_bound(v.begin(), v.end(), c) - v.begin());
        g[a].emplace_back(b, c);
    }
    for(auto& cur : g){
        sort(cur.begin(), cur.end());
        vector<pair<int, int>>nxt;
        int be = -1, en = -1;
        for(auto [b, c] : cur){
            if(b > en){
                if(be != -1) nxt.emplace_back(en, be);
                be = b, en = c;
            }
            else en = max(en, c);
        }
        nxt.emplace_back(en, be);
        swap(nxt, cur);
    }
    int sz = int(v.size());
    vector<vector<int>>table(lg, vector<int>(sz));
    for(int i=0;i<sz;i++) table[0][i] = i;
    for(auto& cur : g){
        for(auto [c, b] : cur) table[0][b] = max(table[0][b], c);
    }
    for(int i=1;i<sz;i++) table[0][i] = max(table[0][i], table[0][i-1]);
    for(int b=1;b<lg;b++){
        for(int i=0;i<sz;i++) table[b][i] = table[b-1][table[b-1][i]];
    }
    for(auto [x, y, z, w] : query){
        y = int(lower_bound(v.begin(), v.end(), y) - v.begin());
        w = int(lower_bound(v.begin(), v.end(), w) - v.begin());
        if(y > w) swap(y, w), swap(x, z);
        int ans = v[w] - v[y];
        {
            int c = int(lower_bound(g[x].begin(), g[x].end(), make_pair(y, 0)) - g[x].begin());
            if(c < g[x].size() && g[x][c].nd <= y) y = g[x][c].st;
        }
        {
            int c = int(lower_bound(g[z].begin(), g[z].end(), make_pair(w, 0)) - g[z].begin());
            if(c < g[z].size() && g[z][c].nd <= w) w = g[z][c].nd;
        }
        if(y >= w){
            cout<< ans + (x != z) <<"\n";
        }
        else if(table[lg-1][y] < w){
            cout<<"-1\n";
        }
        else{
            for(int b=lg-1;b>=0;b--){
                if(table[b][y] < w) ans += 1<<b, y = table[b][y];
            }
            if(y < w) y = table[0][y], ans++;
            cout<<ans + 1<<"\n";
        }
    }

    return 0;
}
