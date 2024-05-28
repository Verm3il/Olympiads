#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


//#define int long long


int n, m;
char a[3030][3030];
int sero[3030][3030], garo[3030][3030];


struct Data{
    int no, garo, sero;
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (a[i][j - 1] == 'R' && a[i][j] == 'G' && a[i][j + 1] == 'W') garo[i][j] = 1;
            if (a[i - 1][j] == 'R' && a[i][j] == 'G' && a[i + 1][j] == 'W') sero[i][j] = 1;
        }
    }

    int ans = 0;
    for (int i=1;i<=n;i++){
        vector<Data> dp = {{0, 0, 0}};
        for (int x=i,y=m,c=1;x<=n&&y>=1;x++,y--,c++){
            dp.push_back({0, 0, 0});
            dp[c].no = max({dp[c - 1].no, dp[c - 1].garo, dp[c - 1].sero});
            dp[c].garo = max(dp[c - 1].no, dp[c - 1].garo) + garo[x][y];
            dp[c].sero = max(dp[c - 1].no, dp[c - 1].sero) + sero[x][y];
        }
        ans += max({dp.back().no, dp.back().garo, dp.back().sero});
    }
    for (int i=1;i<=m-1;i++){
        vector<Data> dp = {{0, 0, 0}};
        for (int x=1,y=i,c=1;x<=n&&y>=1;x++,y--,c++){
            dp.push_back({0, 0, 0});
            dp[c].no = max({dp[c - 1].no, dp[c - 1].garo, dp[c - 1].sero});
            dp[c].garo = max(dp[c - 1].no, dp[c - 1].garo) + garo[x][y];
            dp[c].sero = max(dp[c - 1].no, dp[c - 1].sero) + sero[x][y];
        }
        ans += max({dp.back().no, dp.back().garo, dp.back().sero});
    }
    cout<<ans;

    return 0;
}
