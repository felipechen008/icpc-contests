#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

template<typename T, T (*op)(const T&, const T&)> struct monotonic_queue { // 665a29
    vector<T> as, aas;
    vector<T> bs, bbs;
    void reserve(int N) {
        as.reserve(N); aas.reserve(N);
        bs.reserve(N); bbs.reserve(N);
    }
    void reduce() {
        while (!bs.empty()) {
            as.push_back(bs.back());
            aas.push_back(aas.empty() ? bs.back() : op(bs.back(), aas.back()));
            bs.pop_back(); bbs.pop_back();
        }
    }
    T get() {
        if (as.empty()) reduce();
        return (bbs.empty() ? aas.back() : op(aas.back(), bbs.back()));
    }
    bool empty() const { return (as.empty() && bs.empty()); }
    int size() const { return int(as.size()) + int(bs.size()); }
    T front() {
        if (as.empty()) reduce();
        return as.back();
    }
    void push(const T& val) {
        bs.push_back(val);
        bbs.push_back(bbs.empty() ? val : op(bbs.back(), val));
    }
    void pop() {
        if (as.empty()) reduce();
        as.pop_back();
        aas.pop_back();
    }
};

// min/max
template<typename T> T mapping_min(const T& a, const T& b) {
	return min(a, b);
}
template<typename T> using min_monotonic_queue = monotonic_queue<T, mapping_min>;

template<typename T> T mapping_max(const T& a, const T& b) {
	return max(a, b);
}
template<typename T> using max_monotonic_queue = monotonic_queue<T, mapping_max>;

const int lim = 1e6 + 10;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<lint>t(n), a(n), b(n);
    for(int i=0;i<n;i++) cin>>t[i]>>a[i]>>b[i];
    vector<lint>mx(lim, -linf), mn(lim, linf);
    mx[0] = mn[0] = 0;
    for(int i=0;i<n;i++){
        vector<lint>nmx(lim, -linf), nmn(lim, linf);
        max_monotonic_queue<lint>L;
        min_monotonic_queue<lint>S;
        for(lint j=a[i];j<lim;j++){
            L.push(mx[j-a[i]] - (j-a[i])*t[i]);
            S.push(mn[j-a[i]] - (j-a[i])*t[i]);
            nmx[j] = L.get() + j*t[i];
            nmn[j] = S.get() + j*t[i];
            if(j >= b[i]){
                L.pop();
                S.pop();
            }
        }
        swap(nmx, mx);
        swap(nmn, mn);
    }
    int q;
    cin>>q;
    while(q--){
        lint c, d;
        cin>>c>>d;
        c *= d;
        if(mn[d] <= c && c <= mx[d]) cout<<"yes\n";
        else cout<<"no\n";
    }


    return 0;
}
