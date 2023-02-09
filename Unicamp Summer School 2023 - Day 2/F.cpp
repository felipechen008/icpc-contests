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
    int n, m, k;
    cin>>n>>m>>k;
    if(k % m) {
        cout<<"impossible\n";
        return 0;
    }
    k /= m;

    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int>ids(n);
    iota(ids.begin(), ids.end(), 0);
    sort(ids.begin(), ids.end(), [&](int i, int j){
        return a[i] > a[j];
    });

    int cnt = 0;
    vector<int>ans;

    for(int i=0,l=k-1,r=k;i<n;i++){
        if(r < n && a[ids[r]] * i < cnt * m){
            ans.push_back(ids[r++]);
        }
        else if(l >= 0 && a[ids[l]] * i >= cnt * m){
            cnt++;
            ans.push_back(ids[l--]);
        }
        else break;
    }

    if(size(ans) < n) cout<<"impossible\n";
    else{
        for(int u : ans) cout<<u+1<<" ";
        cout<<"\n";
    }

    return 0;
}
