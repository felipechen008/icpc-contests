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
  int n;
  cin>>n;
  vector<int>a(n);
  for(int i=0;i<n;i++) cin>>a[i];
  lint x = 0, y = 0, ans = 0;
  for(int i=0;i<n;i++){
    if(a[i] == 1) x++;
    if(a[i] == 2) y = (y + y + x) % mod;
    if(a[i] == 3) ans = (ans + y) % mod;
  }
  cout<<ans<<"\n";

  return 0;
}