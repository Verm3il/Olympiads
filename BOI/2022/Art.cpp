#include "art.h"
#include <bits/stdc++.h>


void solve(int N) {
    std::vector<int> order(N);
    std::vector<int> q(N);
    std::iota(order.begin(), order.end(), 1);
    std::vector<int> ans(N);
    std::vector<int> ans2(N);

    for (int i=0;i<N;i++){
        q[i] = publish(order);
        std::rotate(order.begin(), order.begin() + 1, order.end());
    }
    for (int i=0;i<N;i++){
        int s = q[(i + 1) % N] - q[i];
        ans[i] = (s - N - 1) / (-2);
    }
    for (int i=0;i<N;i++){
        ans2[ans[i]-1] = i+1;
    }
    answer(ans2);
}
