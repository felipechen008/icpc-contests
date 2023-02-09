#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int f, s, g, u, d;
  cin>>f>>s>>g>>u>>d;
  vector<int>dist(f+1, inf);
  dist[s] = 0;
  queue<int> q({s});
  while(!q.empty()){
    int v = q.front();
    q.pop();
    if(v + u <= f && dist[v+u] == inf){
      dist[v+u] = dist[v] + 1;
      q.push(v+u);
    }
    if(v - d > 0 && dist[v-d] == inf){
      dist[v-d] = dist[v] + 1;
      q.push(v-d);
    }
  }
  if(dist[g] == inf) cout<<"use the stairs\n";
  else cout<<dist[g]<<"\n";


  return 0;
}