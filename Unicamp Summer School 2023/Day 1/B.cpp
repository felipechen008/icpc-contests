#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<typename T> struct FT {
  vector<T>s;
  FT(int n): s(n) {}
  FT(const vector<T>& A):s(int(A.size())){
    const int N = int(A.size());
    for(int pos = 0; pos < N ; ++pos){
      s[pos] += A[pos];
      int nxt = (pos | (pos + 1));
      if(nxt < N) s[nxt] += s[pos];
    }
  }
  void update(int pos, T dif){
    for(;pos < (int)s.size(); pos |= pos + 1) s[pos] += dif;
  }
  T query(int pos){
    T res = 0;
    for(; pos > 0 ; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin>>n;
  vector<int>a(n);
  for(int i=0;i<n;i++) cin>>a[i], a[i]--;
  FT<lint>one(n), pair(n);
  lint ans = 0;
  for(int i=0;i<n;i++){
    ans += pair.query(n) - pair.query(a[i] + 1);
    pair.update(a[i], one.query(n) - one.query(a[i] + 1));
    one.update(a[i], 1);
  }
  cout<<ans<<"\n";

  return 0;
}