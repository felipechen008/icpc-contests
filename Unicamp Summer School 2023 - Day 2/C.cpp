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
  priority_queue<pair<int, int>>pq;
  vector<int>a(n);
  
  for(int i=0;i<n;i++){
    cin>>a[i];
    if(a[i]) pq.push({a[i], i});
  }
  vector<pair<int, int>>ans;
  while(int(size(pq)) > 1){
    auto [x, i] = pq.top();
    pq.pop();
    auto [y, j] = pq.top();
    pq.pop();
    x--, y--;
    ans.push_back({i+1, j+1});
    if(x) pq.push({x, i});
    if(y) pq.push({y, j});
  }
  if(pq.empty()){
    cout<<"yes\n";
    for(auto [i, j] : ans) cout<<i<<" "<<j<<"\n";
  } 
  else cout<<"no\n";
  


  return 0;
}