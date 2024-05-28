#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    priority_queue<int> pq;
    int n, m, k;
    cin>>n>>m>>k;
    int a, b, c;
    cin>>a>>c>>b;
    int t;
    cin>>t;
    vector<int> s(m+1,0);
    for (int i=1;i<=m;i++)cin>>s[i];
    int ans = 0;
    if (t - c * (n - 1) >= 0) ans++;
    for (int i=1;i<=m-1;i++){
        int nt = t - c * (s[i] - 1);
        int ga = nt / a;
        int nxt = s[i] + ga;
        if (nt < 0) break;
        ans++;
        if (s[i + 1] <= nxt) ga = s[i + 1] - s[i] - 1;
        ans+=ga;
        int x = s[i] + ga + 1;
        if (x == s[i + 1]) continue;
        for (int j=0;j<k-m;j++){
            int rt = t - c * (s[i] - 1) - b * (x - s[i]);
            if (rt < 0) break;
            ga = rt / a;
            nxt = x + ga;
            if (s[i + 1] <= nxt) ga = s[i + 1] - x - 1;
            pq.push(ga+1);
            x+=ga+1;
            if (x == s[i + 1]) break;
        }
    }
    for (int i=0;i<k-m;i++){
        if (pq.empty()) break;
        if (pq.top() < 0) break;
        ans += pq.top();
        pq.pop();
    }
    cout<<ans-1;

    return 0;
}
