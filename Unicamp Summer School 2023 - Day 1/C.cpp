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
  vector<string>s(n);
  for(int i=0;i<n;i++) cin>>s[i];
  int ans = 0;
  for(int i=0;i<n;i++){
    char last = '0';
    int cnt = 0;
    for(char c : s[i]){
      if(last == 'C' && c == 'D') cnt++;
      last = c;
    }
    ans += (!cnt);
  }
  cout<<ans<<"\n";

  return 0;
}