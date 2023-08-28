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
	int n, m;
	cin>>n>>m;
	vector<vector<array<int, 3>>>g(n);
	for(int i=0;i<m;i++){
		int a, b, c;
		cin>>a>>b>>c;
		a--, b--;
		g[a].push_back({b, c, i});
		g[b].push_back({a, c, i});
	}
	vector<lint>dist(n, linf);
    dist[0] = 1;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
	pq.push({0, 0});
	while(!pq.empty()){
		auto [w, u] = pq.top();
		pq.pop();
		if(dist[u] < w) continue;
		for(auto [v, c, i] : g[u]){
			if(dist[v] > dist[u] + c){
				dist[v] = dist[u] + c;
				pq.push({dist[v], v});
			}
		}
	}
	vector<bool>w(n);
	vector<int>ans;
	for(int u=0;u<n;u++){
		for(auto [v, c, i] : g[u]){
			if(dist[v] == dist[u] + c && !w[v]){
				w[v] = 1;
				ans.push_back(i);
			}
		}
	}
	sort(ans.begin(), ans.end());
	for(int u : ans) cout<<u + 1<<" ";
	cout<<"\n";

	
    return 0;
}
