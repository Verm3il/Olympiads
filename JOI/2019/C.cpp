#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

//#define int long long


const int inf = 1e9;
int rig[3];
int pos[404][3];
int a[404];
int dp[404][404][404][3];
int cnt[404][3];
int n;
string s;


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>s;
    for (int i=0;i<n;i++){
        if (s[i] == 'R'){
            a[i+1]=0;
            rig[0]++;
            pos[rig[0]][0]=i+1;
        }
        if (s[i] == 'G'){
            a[i+1]=1;
            rig[1]++;
            pos[rig[1]][1]=i+1;
        }
        if (s[i] == 'Y'){
            a[i+1]=2;
            rig[2]++;
            pos[rig[2]][2]=i+1;
        }
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<3;j++){
            if (a[i + 1] == j) cnt[i + 1][j]++;
            cnt[i + 1][j] += cnt[i][j];
        }
    }
    for (auto &d1: dp) for (auto &d2: d1) for (auto &d3: d2) for (auto &d4: d3) d4 = inf;
    dp[0][0][0][0]=dp[0][0][0][1]=dp[0][0][0][2]=0;
    for (int x=0;x<=rig[0];x++){
        for (int y=0;y<=rig[1];y++){
            for (int z=0;z<=rig[2];z++){
                for (int i=0;i<3;i++){
                    for (int j=0;j<3;j++){
                        if (i == j) continue;
                        if (j == 0 && x == rig[0]) continue;
                        if (j == 1 && y == rig[1]) continue;
                        if (j == 2 && z == rig[2]) continue;
                        int dn = 0;
                        int px, py, pz;
                        int k;
                        if (i == 0){
                            px = pos[x][0];
                            py = (j == 1 ? pos[y + 1][1] : pos[z + 1][2]);
                            pz = (j == 1 ? pos[z][2] : pos[y][1]);
                            k = (j == 1 ? 2 : 1);
                        }
                        if (i == 1){
                            px = pos[y][1];
                            py = (j == 2 ? pos[z + 1][2] : pos[x + 1][0]);
                            pz = (j == 2 ? pos[x][0] : pos[z][2]);
                            k = (j == 2 ? 0 : 2);
                        }
                        if (i == 2){
                            px = pos[z][2];
                            py = (j == 0 ? pos[x + 1][0] : pos[y + 1][1]);
                            pz = (j == 0 ? pos[y][1] : pos[x][0]);
                            k = (j == 0 ? 1 : 0);
                        }
                        dn += max(0, cnt[py][i] - cnt[px][i]);
                        dn += max(0, cnt[py][k] - cnt[pz][k]);
                        dn += dp[x][y][z][i];
                        if (j == 0){
                            dp[x+1][y][z][j] = min(dp[x+1][y][z][j], dn);
                        }
                        if (j == 1){
                            dp[x][y+1][z][j] = min(dp[x][y+1][z][j], dn);
                        }
                        if (j == 2){
                            dp[x][y][z+1][j] = min(dp[x][y][z+1][j], dn);
                        }
                    }
                }
            }
        }
    }
    int ans = inf;
    for (int i=0;i<3;i++){
        ans = min(ans, dp[rig[0]][rig[1]][rig[2]][i]);
    }
    if (ans == inf) ans = -1;
    cout<<ans;
    return 0;
}
