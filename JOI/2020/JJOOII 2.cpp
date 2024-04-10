#include <bits/stdc++.h>

using namespace std;

using ll = long long;


int n, k;
char s[202020];
int pj[202020], po[202020], pi[202020];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k;
    for (int i=1;i<=n;i++) cin>>s[i];

    for (int i=1;i<=n;i++){
        pj[i] = pj[i - 1];
        po[i] = po[i - 1];
        pi[i] = pi[i - 1];
        if (s[i] == 'J') pj[i]++;
        if (s[i] == 'O') po[i]++;
        if (s[i] == 'I') pi[i]++;
    }
    const int mx = 1e9;
    int ans = mx;
    for (int l=1,j=1,o=2,i=3;i<=n;l++){
        while (j <= n && (j < l || pj[j] - pj[l - 1] < k)) j++;
        while (o <= n && (o < j || po[o] - po[j] < k)) o++;
        while (i <= n && (i < o || pi[i] - pi[o] < k)) i++;
        if (j > n || o > n || i > n) break;
        ans = min(ans, (i - l + 1) - (k * 3));
    }
    if (ans==mx)ans=-1;
    cout<<ans;


    return 0;
}
