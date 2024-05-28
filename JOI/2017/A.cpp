#include <bits/stdc++.h>


using namespace std;


using ll = long long;
using vv = vector<vector<ll> >;
using pll = pair<ll, ll>;
using pil = pair<int, ll>;
using pii = pair<int, int>;

using ld = long double;
using pdd = pair<ld, ld>;


#define X first
#define Y second


ll f(ll a, ll b, ll s, ll t){
    if (a > 0 && b > 0){
        return s * (a - b);
    }
    if (a <= 0 && b <= 0){
        return t * (a - b);
    }
    if (a <= 0 && b > 0){
        return +t * a - s * b;
    }
    return s * a - t * b;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    ll s, t;
    cin>>n>>q>>s>>t;
    vector<ll> a(n+2,0), b(n+2,0);
    for (int i=0;i<=n;i++){
        cin>>a[i];
    }
    for (int i=1;i<=n;i++){
        b[i] = a[i] - a[i - 1];
    }
    ll ans = 0;
    for (int i=1;i<=n;i++){
        if (a[i - 1] < a[i]){
            ans += s * (a[i - 1] - a[i]);
        }
        else{
            ans += t * (a[i - 1] - a[i]);
        }
    }
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        ans += f(b[l], b[l] + x, s, t);
        b[l] += x;
        if (r != n){
            ans += f(b[r + 1], b[r + 1] - x, s, t);
            b[r + 1] -= x;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
