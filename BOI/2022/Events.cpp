#include <bits/stdc++.h>

using namespace std;


int n;
int L[101010];
int R[101010];
pair<int, int> seg[808080];
int sp[18][101010];
const int MAX = 1e9;


pair<int, int> operator+(pair<int, int> l, pair<int, int> r) {
    if (l.first > r.first) return l;
    else return r;
}


void initSP() {
    for (int i = 1; i < 18; i++) {
        for (int j = 1; j <= n; j++) {
            sp[i][j] = sp[i - 1][sp[i - 1][j]];
        }
    }
}


void upd(int x, int s, int e, int i, pair<int, int> v) {
    if (e < i || i < s) return;
    if (s == e) {
        seg[x] = v;
        return;
    }
    int m = (s + e) / 2;
    upd(x * 2, s, m, i, v);
    upd(x * 2 + 1, m + 1, e, i, v);
    seg[x] = seg[x * 2] + seg[x * 2 + 1];
}


pair<int, int> getMax(int x, int s, int e, int l, int r) {
    if (e < l || r < s) return {0, 0};
    if (l <= s && e <= r) return seg[x];
    int m = (s + e) / 2;
    return getMax(x * 2, s, m, l, r) + getMax(x * 2 + 1, m + 1, e, l, r);
}


int getAns(int s, int e) {
    if (s == e) return 0;
    if (L[e] < L[s]) {
        return 1e7;
    }
    if (L[e] <= R[s]) {
        return 1;
    }
    if (s == e) return 0;
    int res = 0;
    for (int i = 17; i >= 0; i--) {
        if (L[e] > R[sp[i][s]]) {
            res += (1 << i);
            s = sp[i][s];
        }
    }
    return res + 2;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int query_cnt;
    cin >> n >> query_cnt;
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
        L[i] = MAX - L[i];
        R[i] = MAX - R[i];
        v.push_back(L[i]);
        v.push_back(R[i]);
    }


    // coord compress
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) {
        L[i] = lower_bound(v.begin(), v.end(), L[i]) - v.begin() + 1;
        R[i] = lower_bound(v.begin(), v.end(), R[i]) - v.begin() + 1;
        swap(L[i], R[i]);
    }


    // init seg
    int sz = (int)v.size();
    for (int i = 1; i <= n; i++) {
        if (getMax(1, 1, sz, L[i], L[i]).first > R[i]) continue;
        upd(1, 1, sz, L[i], {R[i], i});
    }


    // init sparse table
    for (int i = 1; i <= n; i++) {
        sp[0][i] = getMax(1, 1, sz, L[i], R[i]).second;
    }
    initSP();


    // query
    while (query_cnt--) {
        int si, ei;
        cin >> si >> ei;
        swap(si, ei);
        int ans = getAns(si, ei);
        if (ans >= n) cout << "impossible\n";
        else cout << ans << '\n';
    }
    return 0;
}
