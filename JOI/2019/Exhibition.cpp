#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vv = vector<vector<ll> >;
using pll = pair<ll, ll>;

using ld = long double;
using pdd = pair<ld,ld>;





int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<pair<int,int> > v(n);
    vector<int> c(m);
    for (int i=0;i<n;i++)cin>>v[i].second>>v[i].first;
    for (int j=0;j<m;j++)cin>>c[j];
    sort(v.begin(),v.end());
    sort(c.begin(),c.end());
    int ans = 0;
    int j=n-1;
    for (int i=m-1;i>=0;i--){
        while (j >= 0 && c[i] < v[j].second) j--;
        if (j < 0) break;
        ans++; j--;
    }
    cout<<ans;
    return 0;
}
