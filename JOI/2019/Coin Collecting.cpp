#include <bits/stdc++.h>

using namespace std;


using ll = long long;
using vv = vector<vector<ll> >;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

using ld = long double;
using pdd = pair<ld,ld>;


int n;
int x[202020], y[202020];
int cnt[202020][3];


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    ll ans = 0;
    for (int i=1;i<=n*2;i++){
        cin>>x[i]>>y[i];
        if (x[i] < 1){
            ans += 1 - x[i];
            x[i] = 1;
        }
        if (x[i] > n){
            ans += x[i] - n;
            x[i] = n;
        }
        if (y[i] < 1){
            ans += 1 - y[i];
            y[i] = 1;
        }
        if (y[i] > 2){
            ans += y[i] - 2;
            y[i] = 2;
        }
        cnt[x[i]][y[i]]++;
    }
    ll p1 = 0, p2 = 0;
    for (int i=1;i<=n;i++){
        p1 += cnt[i][1] - 1;
        p2 += cnt[i][2] - 1;
        while (p1 < 0 && p2 > 0){
            ans++;
            p1++; p2--;
        }
        while (p1 > 0 && p2 < 0){
            ans++;
            p1--; p2++;
        }
        if (i != n) ans += abs(p1) + abs(p2);
    }
    cout<<ans;

    return 0;
}
