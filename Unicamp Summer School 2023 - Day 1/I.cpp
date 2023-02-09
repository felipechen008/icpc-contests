#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const int lim = 20000;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  vector<int>primes, lp(lim);
  for(int i=2;i<lim;i++){
    if(!lp[i]){
      primes.push_back(i);
      for(int j=i;j<lim;j+=i) lp[j] = i;
    }
  }
  vector<array<int, 3>>ans(lim);
  for(int i=0;i<lim;i++) ans[i] = {i, i, i};
  for(int p : primes) ans[p] = {1, p, p};

  auto get = [&](int u)->array<int, 3> {
    auto [a, b, c] = ans[u];
    return array<int, 3>({c, a, b});
  };
  int last = 2;
  for(int p : primes){
    for(int i=p-1;i>last;i--){
      array<int, 3>cur = {i, i, i};
      cur = min(cur, get(i+1));
      for(int q : primes){
        if(q >= i) break;
        if(i % q) continue;
        auto b = get(i/q);
        if(lp[i/q] == i/q) b[2] = i;
        if(cur[0] >= b[0]) cur = b;
      }
      ans[i] = cur;
    }
    last = p;
  }


  int n;
  cin>>n;
  int x = 0, y = 0, z = 0;

  for(int i=0;i<n;i++){
    char ch;
    int k;
    cin>>ch>>k;
    auto [a, b, c] = ans[k];

    if(ch == 'O') x += a, y += b, z += c;
    if(ch == 'E') x += c, y += a, z += b;
    if(ch == 'I') x += b, y += c, z += a;
  }
  cout<<x<<" "<<y<<" "<<z<<"\n";

  return 0;
}