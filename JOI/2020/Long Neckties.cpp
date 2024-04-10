#include <bits/stdc++.h>

using namespace std;

using ll = long long;


int n;
ll a[202020], b[202020], ra[202020];
map<ll, int> idx;
ll p[202020], q[202020];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for (int i=1;i<=n+1;i++){
        cin>>a[i];
        ra[i]=a[i];
    }
    for (int i=1;i<=n;i++){
        cin>>b[i];
    }

    sort(a+1,a+n+2);
    sort(b+1,b+n+1);

    for (int i=1;i<=n+1;i++){
        idx[a[i]] = i;
    }
    for (int i=1;i<=n;i++){
        p[i] = max(p[i - 1], max(0ll, a[i] - b[i]));
    }
    for (int i=n+1;i>=2;i--){
        q[i] = max(q[i + 1], max(0ll, a[i] - b[i - 1]));
    }
    for (int i=1;i<=n+1;i++){
        cout<<max(p[idx[ra[i]]-1], q[idx[ra[i]]+1])<<" \n"[i==n+1];
    }

    return 0;
}
