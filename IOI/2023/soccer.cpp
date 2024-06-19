#include "soccer.h"
#include <bits/stdc++.h>

using namespace std;
#define X first
#define Y second
using pii = pair<int, int>;
using Data = array<int, 4>;

int n;
map<Data, int> dp;
vector<vector<int> > v;

int p[2020][2020];


int sum(int lx, int ly, int rx, int ry){
    lx++; ly++; rx++; ry++;
    return p[rx][ry] - p[lx - 1][ry] - p[rx][ly - 1] + p[lx - 1][ly - 1];
}


pii nxt(int x, int ly, int ry){
    pii ret = {0, 0};
    int lo, hi;
    lo = 0;
    hi = x;
    while (lo <= hi){
        int mid = (lo + hi) / 2;
        if (sum(mid, ly, x, ry)){
            lo = mid + 1;
        }
        else{
            hi = mid - 1;
        }
    }
    ret.X = min(lo, x);
    lo = x;
    hi = n - 1;
    while (lo <= hi){
        int mid = (lo + hi) / 2;
        if (sum(x, ly, mid, ry)){
            hi = mid - 1;
        }
        else{
            lo = mid + 1;
        }
    }
    ret.Y = max(x, hi);
    return ret;
}


vector<pii> g(int i, int l, int r){
    vector<pii> ret;

    int k = l;
    for (int j=l;j<=r;j++){
        if (v[i][j]){
            if (k <= j - 1){
                ret.emplace_back(k, j - 1);
            }
            k = j + 1;
        }
    }
    if (k <= r){
        ret.emplace_back(k, r);
    }

    return ret;
}


int f(int lx, int ly, int rx, int ry){
    if (dp.count({lx, ly, rx, ry})){
        return dp[{lx, ly, rx, ry}];
    }
    int res = 0;

    if (lx){
        vector<pii> cand = g(lx - 1, ly, ry);
        for (auto &[nyX, nyY]: cand){
            auto [nxX, nxY] = nxt(lx - 1, nyX, nyY);
            res = max(res, f(nxX, nyX, nxY, nyY)
                        + (nxY - nxX - rx + lx) * (nyY - nyX + 1));
        }
    }

    if (rx < n - 1){
        vector<pii> cand = g(rx + 1, ly, ry);
        for (auto &[nyX, nyY]: cand){
            auto [nxX, nxY] = nxt(rx + 1, nyX, nyY);
            res = max(res, f(nxX, nyX, nxY, nyY)
                           + (nxY - nxX - rx + lx) * (nyY - nyX + 1));
        }
    }

    return dp[{lx, ly, rx, ry}] = res;
}


int biggest_stadium(int N, vector<vector<int> > F){
    n = N;
    v = F;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + v[i - 1][j - 1];
        }
    }

    int ans = 0;
    for (int i=0;i<n;i++){
        vector<pii> cand = g(i, 0, n - 1);
        for (auto &[nyX, nyY]: cand){
            auto [nxX, nxY] = nxt(i, nyX, nyY);
            ans = max(ans, f(nxX, nyX, nxY, nyY)
                    + (nxY - nxX + 1) * (nyY - nyX + 1));
        }
    }

    return ans;
}
