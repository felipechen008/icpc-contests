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
    string a, b;
    cin>>a>>b;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int n = int(max(size(a), size(b))) + 1;
    while(size(a) < n) a.push_back('0');
    while(size(b) < n) b.push_back('0');

    auto get_sum = [&](string s, string t)->string {
        string c; c.resize(n);
        for(int i=0;i<n;i++){
            c[i] += s[i] + t[i] - '0';
            if(c[i] > '9'){
                c[i] -= 10;
                c[i+1]++;
            }
        }
        return c;
    };

    auto get_diff = [&](string s, string t)->string {
        string c; c.resize(n);
        for(int i=0;i<n;i++){
            c[i] += s[i] - t[i] + '0';
            if(c[i] < '0'){
                c[i] += 10;
                c[i+1]--;
            }
        }
        return c;
    };

    auto get_min = [&](string s, string t)->string {
        for(int i=n-1;i>=0;i--){
            if(s[i] == t[i]) continue;
            if(s[i] < t[i]) return s;
            else return t;
        }
        return s;
    };

    string sum = get_sum(a, b);
    string ans = "0";

    for(int i=n-1;i>=0;i--){
        if(a[i] <= sum[i]) continue;
        string large, small;
        small.resize(n);
        for(int j=n-1;j>i;j--) small[j] = a[j];
        for(int j=i;j>=0;j--) small[j] = sum[j];
        if(a[i+1] < sum[i+1]){
            large.resize(n);
            for(int j=n-1;j>i;j--) large[j] = a[j];
            large[i+1] = a[i+1] + 1;
            for(int j=i;j>=0;j--) large[j] = '0';
            ans = get_min(get_diff(large, a), get_diff(a, small));
        }
        else ans = get_diff(a, small);

        break;
    }
    while(size(ans) > 1 && ans.back() == '0') ans.pop_back();
    reverse(ans.begin(), ans.end());

    cout<<ans<<"\n";


    return 0;
}
