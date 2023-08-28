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
    char s1, s2, s3;
    char t1, t2, t3;
    cin>>s1>>s2>>s3;
    cin>>t1>>t2>>t3;
    int cnt = 0;
    if(s1 == t2) swap(s1, s2), cnt++;
    if(s1 == t3) swap(s1, s3), cnt++;
    if(s2 == t3) swap(s2, s3), cnt++;
    if(s1 == t2) swap(s1, s2), cnt++;
    if(s1 == t3) swap(s1, s3), cnt++;
    if(s2 == t3) swap(s2, s3), cnt++;
    if(cnt&1) cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}
