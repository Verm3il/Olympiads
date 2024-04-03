#include "stations.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;
vector<int> g[MAXN];
int num = 0;
int res[MAXN];

void dfs(int x, int bef, int col){
    if (col & 1) {
        res[x] = num++;
    }
    for (int i: g[x]){
        if (i == bef) continue;
        dfs(i, x, col ^ 1);
    }
    if (~col & 1) {
        res[x] = num++;
    }
}

std::vector<int> label(int n, int k, std::vector<int> u, std::vector<int> v) {
	std::vector<int> labels(n);
    for (int i=0;i<n-1;i++){
        g[u[i]].push_back(v[i]);
        g[v[i]].push_back(u[i]);
    }
    dfs(0, -1, 0);
	for (int i = 0; i < n; i++) {
		labels[i] = res[i];
//        cout<<labels[i]<<endl;
	}

    num = 0;
    for (int i=0;i<n;i++){
        g[i].clear();
        res[i] = 0;
    }
	return labels;
}

int find_next_station(int s, int t, std::vector<int> c) {
//    for (int i: c){ cout<<i<<" "; }cout<<endl;
    if (c.size()==1){
        return c[0];
    }
    if (s < c[0]){
        int bef = s + 1;
        for (int i=0;i<c.size();i++){
            if (bef <= t && t <= c[i]) return c[i];
            bef = c[i] + 1;
        }
        return c[c.size()-1];
    }
    else{
        int bef = s - 1;
        for (int i=c.size()-1;i>=0;i--){
            if (c[i] <= t && t <= bef) return c[i];
            bef = c[i] - 1;
        }
        return c[0];
    }
}
