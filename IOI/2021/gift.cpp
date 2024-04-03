#include "gift.h"

int par[505050];
char c[] = {'B', 'R'};
int blue[505050], red[505050];

int find(int x){
    if (x == par[x]) return x;
    return par[x] = find(par[x]);
}

void uni(int x, int y){
    x = find(x); y = find(y);
    if (x > y) std::swap(x, y);
    par[x] = y;
}

int construct(int n, int r, std::vector<int> a, std::vector<int> b, std::vector<int> x) {
    std::string s;
    for (int i=0;i<n;i++)par[i]=i;
    for (int i=0;i<r;i++){
        if (x[i] == 2) continue;
        int j = a[i];
        while (j < b[i]){
            uni(j, j + 1);
            j = find(j);
        }
    }
    int j = 0;
    for (int i=0;i<n;i++){
        s += c[j];
        if (find(i) == i) j ^= 1;
    }
    for (int i=1;i<=n;i++){
        blue[i] = blue[i - 1] + (s[i - 1] == 'B');
         red[i] =  red[i - 1] + (s[i - 1] == 'R');
    }
    for (int i=0;i<r;i++){
        b[i]++;
        int cnt = 0;
        if (blue[b[i]] - blue[a[i]]) cnt++;
        if ( red[b[i]] -  red[a[i]]) cnt++;
        if (cnt != x[i]) return 0;
    }
    craft(s);
    return 1;
}
