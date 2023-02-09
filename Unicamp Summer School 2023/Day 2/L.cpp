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
    vector<string>s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    bool sw = false;
    if(n > m){
        sw = true;
        vector<string>t(m);
        for(int i=0;i<m;i++){
            t[i].resize(n);
            for(int j=0;j<n;j++) t[i][j] = s[j][i];
        }
        swap(s, t);
        swap(n, m);
    }

    vector<string>A(n), B(n), C(n);
    {
        string emp;
        emp.resize(m, '.');
        for(int i=0;i<n;i++) A[i] = B[i] = C[i] = emp;
    }

    if(n == 1){
        char last = '1', comp = 0;
        int be1 = -1, en1 = -1;
        int be2 = -1, en2 = -1;
        for(int i=0;i<m;i++){
            if(s[0][i] != last){
                if(s[0][i] == '2'){
                    comp++;
                    if(be1 == -1) be1 = i;
                    else be2 = i;
                }
                else{
                    if(en1 == -1) en1 = i;
                    else en2 = i; 
                }
            }
            last = s[0][i];
        }
        if(be1 != -1 && en1 == -1) en1 = m;
        if(be2 != -1 && en2 == -1) en2 = m;

        if(comp > 2){
            cout<<"impossible\n";
            return 0;
        }
        if(comp == 2){
            for(int i=0;i<en1;i++) A[0][i] = 'A';
            for(int i=be1;i<en2;i++) B[0][i] = 'B';
            for(int i=be2;i<m;i++) C[0][i] = 'C';
        }
        else if(comp == 1){
            for(int i=0;i<m;i++) A[0][i] = 'A';
            for(int i=be1;i<en1;i++) B[0][i] = 'B';
            for(int i=be1;i<en1;i++) C[0][i] = 'C';
        }
        else{
            if(m < 3){
                cout<<"impossible\n";
                return 0;
            }
            for(int i=0;i<m-2;i++) A[0][i] = 'A';
            B[0][m-2] = 'B';
            C[0][m-1] = 'C';
        }
    }
    else{
        vector<string>aux(n);
        for(int i=0;i<n-1;i++) aux[i].resize(m, '.');
        aux[n-1].resize(m, 'C');
        vector<int>mx = {0, n-2, m-1, 1};
        aux[0][m-1] = 'B';
        for(int i=0,x=0,y=m-1;;i=(i+1)%4){
            int cnt = 0;
            if(i == 0){
                while(y - 1 > mx[i]){
                    cnt++, y--;
                    aux[x][y] = 'B';
                }
                mx[i] += 2;
            }
            else if(i == 1){
                while(x + 1 < mx[i]){
                    cnt++, x++;
                    aux[x][y] = 'B';
                }
                mx[i] -= 2;
            }
            else if(i == 2){
                while(y + 1 < mx[i]){
                    cnt++, y++;
                    aux[x][y] = 'B';
                }
                mx[i] -= 2;
            }
            else{
                while(x - 1 > mx[i]){
                    cnt++, x--;
                    aux[x][y] = 'B';
                }
                mx[i] += 2;
            }

            if(!cnt) break;
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++) if(aux[i][j] == '.') aux[i][j] = 'A';
        }

        if(n == 4){
            for(int i=0;i<m;i++) aux[0][i] = 'B';
            for(int i=0;i<m;i++) aux[1][i] = 'A';
            for(int i=0;i<m;i++) aux[2][i] = 'A';
            for(int i=0;i<m;i++) aux[3][i] = 'C';
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(aux[i][j] == 'A') A[i][j] = 'A';
                if(aux[i][j] == 'B') B[i][j] = 'B';
                if(aux[i][j] == 'C') C[i][j] = 'C';
            }
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(s[i][j] == '2'){
                    for(auto [x, y] : vector<pair<int, int>>({{0, 1}, {0, -1}, {1, 0}, {-1, 0}})){
                        int ni = i + x, nj = j + y;
                        if(ni < 0 || ni >= n || nj < 0 || nj >= m || aux[i][j] == aux[ni][nj]) continue;
                        if(aux[ni][nj] == 'A') A[i][j] = 'A';
                        if(aux[ni][nj] == 'B') B[i][j] = 'B';
                        if(aux[ni][nj] == 'C') C[i][j] = 'C';
                        break;
                    }
                }
            }
        }

    }
    if(!sw){
        for(int i=0;i<n;i++) cout<<A[i]<<"\n";
        cout<<"\n";
        for(int i=0;i<n;i++) cout<<B[i]<<"\n";
        cout<<"\n";
        for(int i=0;i<n;i++) cout<<C[i]<<"\n";
    }
    else{
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++) cout<<A[j][i];
            cout<<"\n";
        }
        cout<<"\n";
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++) cout<<B[j][i];
            cout<<"\n";
        }
        cout<<"\n";
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++) cout<<C[j][i];
            cout<<"\n";
        }
    }


    return 0;
}
