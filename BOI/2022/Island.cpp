#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;


ll a[202020];
struct DSU{
    vector<int> p;
    vector<ll> dp;
    vector<vector<int> > v;
    int n;
    DSU(int _n){
        n = _n;
        p.resize(n);
        for (int i=0;i<n;i++) dp.emplace_back(a[i]);
        v.resize(n);
        iota(p.begin(),p.end(),0);
        for (int i=0;i<n;i++) v[i].push_back(i);
    }

    int fnd(int x){
        if (x == p[x]) return x;
        return p[x] = fnd(p[x]);
    }

    void uni(int x, int y, bool mer){
        x = fnd(x); y = fnd(y);
        if (x == y) return;
        p[y] = x;
        dp[x] += dp[y];
        if (mer){
            if (v[x].size() < v[y].size()) swap(v[x], v[y]);
            for (int i: v[y]) v[x].push_back(i);
        }
    }
};


bool cmp(pii p1, pii p2){
    return pii(a[p1.first], a[p1.second]) < pii(a[p2.first], a[p2.second]);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;cin>>n>>m;
    for (int i=0;i<n;i++)cin>>a[i];
    vector<pair<int, int> > e;
    for (int i=0;i<m;i++){
        int u,v;cin>>u>>v;u--;v--;
        if (a[u] >= a[v]) e.emplace_back(u, v);
        else e.emplace_back(v, u);
    }
    sort(e.begin(),e.end(),cmp);
    DSU dsu(n);
    for (auto [u, v]: e){
        int V = dsu.fnd(v);
        if (dsu.dp[V] < a[u]) dsu.uni(u, v, false);
        else dsu.uni(u, v, true);
    }
    vector<int>ans(n,0);
    for (int i:dsu.v[dsu.fnd(0)])ans[i]=1;
    for (int i=0;i<n;i++)cout<<ans[i];
    cout<<'\n';
}
