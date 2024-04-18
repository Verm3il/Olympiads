#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vv = vector<vector<ll> >;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<int> a(n), b(m);
    for (int i=0;i<n;i++)cin>>a[i];
    for (int i=0;i<m;i++)cin>>b[i];
    vector<int> rem(1<<m,-1), c(1<<m,-1);
    rem[0] = c[0] = 0;
    for (int bit=0;bit<(1<<m);bit++){
        for (int i=0;i<m;i++){
            if (!((bit >> i) & 1)) continue;
            int bef = bit - (1 << i);
            if (c[bef] == -1) continue;
            if (rem[bef] + b[i] < a[c[bef]]){
                rem[bit] = rem[bef] + b[i];
                c[bit] = c[bef];
            }
            else if (rem[bef] + b[i] == a[c[bef]]){
                rem[bit] = 0;
                c[bit] = c[bef] + 1;
            }
        }
        if (c[bit] == n){
            cout<<"YES";
            return 0;
        }
    }
    cout<<"NO";
    return 0;
}
