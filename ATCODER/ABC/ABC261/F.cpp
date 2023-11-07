#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<typename T> struct FT { // 8b7639
    vector<T> s;
    FT(int n) : s(n) {}
    FT(const vector<T>& A) : s(A) {
        const int N = int(s.size());
        for (int a = 0; a < N; ++a)
            if ((a | (a + 1)) < N) s[a | (a + 1)] += s[a];
    }
    void update(int pos, T dif) { // a[pos] += dif
        for (; pos < (int)s.size(); pos |= pos + 1) s[pos] += dif;
    }
    T query(int pos) { // sum of values in [0, pos)
        T res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    // min pos st sum of [0, pos] >= sum. Returns n if no sum
    int lower_bound(T sum) { //is >= sum, or -1 if empty sum is.
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)
            if (pos + pw <= (int)s.size() && s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        return pos;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int>c(n), x(n);
    for(int i=0;i<n;i++) cin>>c[i], c[i]--;
    for(int i=0;i<n;i++) cin>>x[i], x[i]--;
    vector<vector<int>>vals(n);
    vector<FT<int>>seg_color(n, FT<int>(0));
    FT<int>seg(n);
    for(int i=0;i<n;i++) vals[c[i]].push_back(x[i]);
    for(auto& v : vals){
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    for(int i=0;i<n;i++) seg_color[i] = FT<int>((int)vals[i].size());
    lint ans = 0;
    for(int i=n-1;i>=0;i--){
        auto& v = vals[c[i]];
        int u = int(lower_bound(v.begin(), v.end(), x[i]) - v.begin());
        int cur = seg.query(x[i]) - seg_color[c[i]].query(u);
        seg.update(x[i], 1);
        seg_color[c[i]].update(u, 1);
        ans += cur;
    }
    cout<<ans<<"\n";
    return 0;
}
