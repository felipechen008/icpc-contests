#include <bits/stdc++.h>
#define st first
#define nd second
using lint = long long;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr lint linf = 0x3f3f3f3f3f3f3f3f;
using namespace std;

lint query(int a, int b){
    cout<<"? "<<a<<" "<<b<<endl;
    lint x;
    cin>>x;
    return x;
}

void answer(lint x){
    cout<<"! "<<x<<endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<lint>qr(50);
    lint x = query(1, 50);
    if(x == -1){
        for(int i=49;i>=1;i--){
            x = query(1, i);
            if(x != -1){
                answer(i);
                break;
            }
        }
    }
    else{
        qr[0] = x;
        qr[1] = query(50, 1);
        for(int i=1;i<25;i++){
            int a = i + 1, b = 50 - i;
            qr[2*i] = query(a, b);
            qr[2*i+1] = query(b, a);
        }
        map<lint, lint>f;
        for(int i=0;i<25;i++){
            f[qr[2*i] + qr[2*i+1]]++;
        }
        lint cnt = 0, ans = -1;
        for(auto [a, b] : f){
            if(cnt < b) cnt = b, ans = a;
        }
        answer(ans);
    }
    return 0;
}
