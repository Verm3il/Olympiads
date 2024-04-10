#include <bits/stdc++.h>
using namespace std;


int n, m;
int a[2020][2020];
int ans = 1e9;
int mx = 0;
int mn = 1e9;


bool f(int k){
    int r = 1;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (a[i][j] < mx - k){
                r = max(r, j + 1);
            }
        }
        for (int j=1;j<r;j++){
            if (a[i][j] > mn + k){
                return false;
            }
        }
    }
    return true;
}


void flip1(){
    for (int i=1;i<=n/2;i++){
        for (int j=1;j<=m;j++){
            swap(a[i][j], a[n - i + 1][j]);
        }
    }
}


void flip2(){
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m/2;j++){
            swap(a[i][j], a[i][m - j + 1]);
        }
    }
}


void g(){
    int lo = 0;
    int hi = mx - mn;
    while (lo <= hi){
        int mid = (lo + hi) / 2;
        if (f(mid)) hi = mid - 1;
        else lo = mid + 1;
    }
    ans = min(ans, lo);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            cin>>a[i][j];
            mx = max(mx, a[i][j]);
            mn = min(mn, a[i][j]);
        }
    }
    g();
    flip2();
    g();
    flip1();
    g();
    flip2();
    g();
    cout<<ans;
    return 0;
}
