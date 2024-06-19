#include "longesttrip.h"
#include <bits/stdc++.h>

using namespace std;

std::vector<int> longest_trip(int n, int D)
{
    int cnt = 0;

    vector<int> r1, r2;
    r1.push_back(n - 1);
    if (~n & 1){
        cnt++;
        if (are_connected({n - 2}, {n - 1})){
            r1.push_back(n - 2);
        }
        else{
            r2.push_back(n - 2);
        }
    }

    for (int i=0;i<n-2;i+=2){
        if (r2.empty()){
            bool con = are_connected({i}, {i + 1});
            bool n1 = are_connected({i}, {r1.back()});
            bool n2 = are_connected({i + 1}, {r1.back()});
            cnt += 3;
            if (con){
                if (n1){
                    r1.push_back(i);
                    r1.push_back(i + 1);
                }
                else if (n2){
                    r1.push_back(i + 1);
                    r1.push_back(i);
                }
                else{
                    r2.push_back(i);
                    r2.push_back(i + 1);
                }
            }
            else{
                if (n1){
                    r1.push_back(i);
                    r2.push_back(i + 1);
                }
                else{
                    r1.push_back(i + 1);
                    r2.push_back(i);
                }
            }
        }
        else{
            cnt++;
            bool l1 = are_connected({i}, {r1.back()});
            if (!l1){
                swap(r1, r2);
            }
            bool con = are_connected({i}, {i + 1});
            cnt++;
            if (con){
                bool h2 = are_connected({i + 1}, {r2.back()});
                cnt++;
                r1.push_back(i);
                r1.push_back(i + 1);
                if (h2){
                    reverse(r2.begin(), r2.end());
                    for (int j: r2){
                        r1.push_back(j);
                    }
                    r2.clear();
                }
                else{
                    // do nothing
                }
            }
            else{
                bool h2 = are_connected({i + 1}, {r2.back()});
                cnt++;
                if (h2){
                    r1.push_back(i);
                    r2.push_back(i + 1);
                }
                else{
                    r1.push_back(i + 1);
                    r2.push_back(i);
                }
            }
        }
    }

    if (r1.size() < r2.size()){
        swap(r1, r2);
    }
//    for (int i: r1) cout<<i<<" "; cout<<endl;
//    for (int i: r2) cout<<i<<" "; cout<<endl;
    if (r2.empty() || !are_connected(r1, r2)){
        return r1;
    }
    cnt++;
//    cout<<"F"<<endl;
    if ((r1.size() <= 2 || are_connected({r1[0]}, {r1.back()})) &&
            (r2.size() <= 2 || are_connected({r2[0]}, {r2.back()}))){
        vector<int> cand;
        for (int i: r1){
            cand.push_back(i);
        }

        int lo1 = 0;
        int hi1 = (int)cand.size() - 1;
        while (lo1 < hi1){
            int mid = (lo1 + hi1) / 2;
            vector<int> v;
            for (int i=lo1;i<=mid;i++){
                v.push_back(cand[i]);
            }
            cnt++;
            if (are_connected(v, r2)){
                hi1 = mid;
            }
            else{
                lo1 = mid + 1;
            }
        }
        int lv = lo1;
        vector<int> lvv = {cand[lv]};

        cand.clear();
        for (int i: r2){
            cand.push_back(i);
        }
        int lo2 = 0;
        int hi2 = (int)cand.size() - 1;
        while (lo2 < hi2){
            int mid = (lo2 + hi2) / 2;
            vector<int> v;
            for (int i=lo2;i<=mid;i++){
                v.push_back(cand[i]);
            }
            cnt++;
            if (are_connected(v, lvv)){
                hi2 = mid;
            }
            else{
                lo2 = mid + 1;
            }
        }
        int rv = lo2;

//    cout<<lvv[0]<<" "<<r2[rv]<<endl;
//    cout<<"QRY: "<<cnt<<endl;

        vector<int> ret;
        rotate(r2.begin(), r2.begin() + rv, r2.end());
        reverse(r2.begin(), r2.end());
        for (int i: r2){
            ret.push_back(i);
        }
        for (int i=0;i<r1.size();i++){
            ret.push_back(r1[(i + lv) % r1.size()]);
        }

        return ret;
    }

    if (are_connected({r1[0]}, {r2[0]})){
        reverse(r2.begin(), r2.end());
        for (int i: r1){
            r2.push_back(i);
        }
        return r2;
    }

    if (are_connected({r1[0]}, {r2.back()})){
        for (int i: r1){
            r2.push_back(i);
        }
        return r2;
    }

    if (are_connected({r1.back()}, {r2[0]})){
        for (int i: r2){
            r1.push_back(i);
        }
        return r1;
    }

    if (are_connected({r1.back()}, {r2.back()})){
        reverse(r2.begin(), r2.end());
        for (int i: r2){
            r1.push_back(i);
        }
        return r1;
    }

    assert(0);
}
