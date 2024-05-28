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


const int mx = 2e5 + 5;


struct BIT{
    ll tree[mx * 2];
    int n = mx * 2;


    void upd(int i, ll v){
        while (i < n){
            tree[i] += v;
            i += (i & -i);
        }
    }


    ll qry(int i){
        ll ret = 0;
        while (i){
            ret += tree[i];
            i -= (i & -i);
        }
        return ret;
    }
};


struct DS{
    BIT bit1, bit2;
    void upd(int i, ll v){
        i += mx;
        bit1.upd(1, v);
        bit1.upd(i + 1, -v);
        bit2.upd(i + 1, v * i);
    }

    ll qry(int i){
        i += mx;
        return bit1.qry(i) * i + bit2.qry(i);
    }
}ds1, ds2;


int n, q;
int a[202020], L[202020], R[202020];
ll pf[202020];
ll ans[202020];
vector<pii> upd[202020], qry[202020];


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    stack<int> st;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        pf[i] = pf[i - 1] + a[i];
        while (!st.empty() && a[i] > a[st.top()]){
            R[st.top()] = i;
            st.pop();
        }
        if (!st.empty()){
            L[i] = st.top();
        }
        st.push(i);
    }

    for (int i=1;i<=n;i++){
        if (L[i]){
            upd[i - L[i]].emplace_back(i, a[L[i]] - a[i]);
            if (R[i]){
                upd[R[i] - L[i]].emplace_back(R[i], a[i] - a[L[i]]);
            }
        }
    }

    for (int i=1;i<=q;i++){
        int t, l, r;
        cin>>t>>l>>r;
        ans[i] += pf[r] - pf[l - 1];
        qry[t].emplace_back(l - 1, -i);
        qry[t].emplace_back(r, i);
    }

    for (int i=1;i<=n;i++){
        for (auto [A, B]: upd[i]){
            ds1.upd(A - i, B);
            ds2.upd(A - 1, B);
        }
        for (auto [A, B]: qry[i]){
            if (B > 0){
                ans[B] += ds1.qry(A - i) - ds2.qry(A);
            }
            else{
                ans[-B] -= ds1.qry(A - i) - ds2.qry(A);
            }
        }
    }
    for (int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }

    return 0;
}
