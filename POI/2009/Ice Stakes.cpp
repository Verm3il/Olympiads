#include <bits/stdc++.h>


using namespace std;


using ll = long long;
using vv = vector<vector<ll> >;
using pll = pair<ll, ll>;
using pil = pair<int, ll>;
using pii = pair<int, int>;

using ld = long double;
using pdd = pair<ld,ld>;


int n,m;
ll k,d;
struct Node{
    ll mx, ls, rs, s;
    Node operator + (const Node &rhs) const{
        Node ret{};
        ret.ls = max(ls, s + rhs.ls);
        ret.rs = max(rhs.rs, rhs.s + rs);
        ret.s = s + rhs.s;
        ret.mx = max({rs + rhs.ls, mx, rhs.mx});
        return ret;
    }
}seg[808080];


void upd(int x, int s, int e, int i, ll v){
    if (e < i || i < s) return;
    if (s == e){
        seg[x] = {v,v,v,v};
        return;
    }
    int mi = (s+e)/2;
    upd(x*2,s,mi,i,v);
    upd(x*2+1,mi+1,e,i,v);
    seg[x]=seg[x*2]+seg[x*2+1];
}

ll a[202020];
void check(){
    cout<<vector<string>({"NIE\n","TAK\n"})[seg[1].mx<=k*d];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>k>>d;
    for (int i=1;i<=n;i++){
        a[i]=-k;
        upd(1,1,n,i,a[i]);
    }
    while(m--){
        int r;
        ll x;
        cin>>r>>x;
        a[r]+=x;
        upd(1,1,n,r,a[r]);
        check();
    }
    return 0;
}
