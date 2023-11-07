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
        for (int a = 0; a < N; ++a) {
            if ((a | (a + 1)) < N) s[a | (a + 1)] += s[a];
        }
    }
    void update(int pos, T dif) { // a[pos] += dif
        for (; pos < (int)s.size(); pos |= pos + 1) s[pos] += dif;
    }
    T query(int pos) { // sum of values in [0, pos)
        T res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    int lower_bound(T sum) {// min pos st sum of [0, pos] >= sum
        // Returns n if no sum is >= sum, or -1 if empty sum is.
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= (int)s.size() && s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q;
    cin>>n>>m>>q;
    vector<array<int, 4>>queries(q+1);
    vector<lint>ans(q+1);
    vector<int>last(n);
    vector<vector<int>>ind(q+1);
    for(int i=1;i<=q;i++){
        int op, l, r, x = -1;
        cin>>op>>l>>r;
        l--;
        if(op == 1){
            cin>>x;
        }
        else if(op == 2) last[l] = i;
        else{
            ind[last[l]].push_back(i);
            ans[i] += queries[last[l]][2];
        }
        queries[i] = {op, l, r, x};
    }
    FT<lint>seg(m + 1);
    for(int i=0;i<=q;i++){
        for(auto j : ind[i]){
            auto [op, l, r, x] = queries[j];
            ans[j] -= seg.query(r);
        }
        if(!i) continue;
        auto [op, l, r, x] = queries[i];
        if(op == 1){
            seg.update(l, x);
            seg.update(r, -x);
        }
        else if(op == 2){

        }
        else{
            ans[i] += seg.query(r);
            cout<<ans[i]<<"\n";
        }
    }
    return 0;
}
