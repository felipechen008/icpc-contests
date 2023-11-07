#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

const lint lim = 100100;

struct segtree {
    int n; 
    vector<lint>s;
    vector<int>mx, mn, lz, lz2;
    segtree(int N): n(1<<__lg(2*N-1)), s(2*n), mx(2*n), mn(2*n, inf), lz(2*n), lz2(2*n, 1){}
    void prep(int v, int val){
        s[v + n] = val;
        mx[v + n] = mn[v + n] = val;
    }
    void build(){
        for(int v=n;--v;){
            mx[v] = max(mx[2*v], mx[2*v+1]);
            mn[v] = min(mn[2*v], mn[2*v+1]);
            s[v] = s[2*v] + s[2*v+1];
        }
    }
    void push(int v, int l, int r){
        if(lz[v]){
            mx[v] = mn[v] = lz[v]; 
            if(l != r){
                lz[2*v] = lz[v];
                lz[2*v+1] = lz[v];

                lz2[2*v] = 1;
                lz2[2*v+1] = 1;
            }
            s[v] = lint(mx[v]) * (r - l + 1);
            lz[v] = 0;
        }
        if(lz2[v] != 1){
            mx[v] /= lz2[v];
            mn[v] /= lz2[v];
            if(l != r){
                lz2[2*v] = min( lint(lz2[2*v])*lz2[v], lim );
                lz2[2*v+1] = min( lint(lz2[2*v+1])*lz2[v], lim );
            }
            s[v] = lint(mx[v]) * (r - l + 1);
            lz2[v] = 1;
        }
    }
    void update(int v, int l, int r, int a, int b, int x){
        push(v, l, r);
        if(r < a || b < l) return;
        if(a <= l && r <= b){
            lz[v] = x, lz2[v] = 1;
            push(v, l, r);
            return;
        }
        int m = (l + r) >> 1;
        update(2*v, l, m, a, b, x);
        update(2*v+1, m+1, r, a, b, x);
        mx[v] = max(mx[2*v], mx[2*v+1]);
        mn[v] = min(mn[2*v], mn[2*v+1]);
        s[v] = s[2*v] + s[2*v+1];
    }
    void update(int a, int b, int x){
        update(1, 0, n-1, a, b, x);
    }
    void update2(int v, int l, int r, int a, int b, int x){
        push(v, l, r);
        if(r < a || b < l) return;
        if(a <= l && r <= b && mx[v] == mn[v]){
            lz2[v] = min( lint(lz2[v])*x, lim );
            push(v, l, r);
            return;
        }
        int m = (l + r) >> 1;
        update2(2*v, l, m, a, b, x);
        update2(2*v+1, m+1, r, a, b, x);
        mx[v] = max(mx[2*v], mx[2*v+1]);
        mn[v] = min(mn[2*v], mn[2*v+1]);
        s[v] = s[2*v] + s[2*v+1];
    }
    void update2(int a, int b, int x){
        update2(1, 0, n-1, a, b, x);
    }
    lint query(int v, int l, int r, int a, int b){
        push(v, l, r);
        if(r < a || b < l) return 0;
        if(a <= l && r <= b) return s[v];
        int m = (l + r) >> 1;
        return query(2*v, l, m, a, b) + query(2*v+1, m+1, r, a, b);
    }
    lint query(int a, int b){
        return query(1, 0, n-1, a, b);
    }

};



int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin>>n>>q;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    segtree seg(n);
    for(int i=0;i<n;i++) seg.prep(i, a[i]);
    seg.build();
    while(q--){
        int op, l, r;
        cin>>op>>l>>r;
        l--, r--;
        if(op == 1){
            int x;
            cin>>x;
            seg.update2(l, r, x);
        }
        else if(op == 2){
            int x;
            cin>>x;
            seg.update(l, r, x);
        }
        else{
            cout<<seg.query(l, r)<<"\n";
        }

    }
    return 0;
}
