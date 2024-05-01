#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vv = vector<vector<ll> >;
using pll = pair<ll, ll>;

using ld = long double;
using pdd = pair<ld,ld>;


int h,w;
ll ans = 0;
string s[3030];
ll O[3030][3030], I[3030][3030];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>h>>w;
    for (int i=0;i<h;i++){
        cin>>s[i];
        for (int j=0;j<w;j++){
            if (s[i][j] == 'I') O[i+1][j+1]++;
            if (s[i][j] == 'O') I[i+1][j+1]++;
        }
    }
    for (int i=0;i<h;i++) for (int j=0;j<w;j++){
        O[i+1][j+1] += O[i][j+1];
        I[i+1][j+1] += I[i+1][j];
    }
    for (int i=0;i<h;i++){
        for (int j=0;j<w;j++){
            if (s[i][j] == 'J'){
                ans += (O[h][j+1]-O[i+1][j+1]) * (I[i+1][w]-I[i+1][j+1]);
            }
        }
    }
    cout<<ans;
    return 0;
}
