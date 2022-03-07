---
layout: post
title: problem A.
---


#include <bits/stdc++.h>
using namespace std;

const int maxn = 210;
int a[maxn];
int dp[maxn][maxn];

struct Data {
    int sum;
    int l,r;
};

int main() {
    int k, n;
    cin>>k>>n;
    for (int i=1; i<=n; ++i) {
        cin>>a[i];
        a[n+i]=a[i];
    }
    for (int i=1; i<=2*n; ++i) {
        a[i] += a[i-1];
    }
    vector<Data> d;
    for (int i=0; i<n; ++i) {
        for (int j=1; j<=n; ++j) {
            d.push_back({a[i+j]-a[i], i, i+j});
        }
    }
    sort(d.begin(), d.end(), [](auto p, auto q) {
        return p.sum < q.sum;
    });
    vector<int> s(n+1);
    auto check = [&](int L, int R, int rot)->bool {
        for (int i = 1; i <= n; ++i) {
            s[i] = a[rot+i] - a[rot+i-1];
            s[i] += s[i-1];
        }
        for (int i=0; i<=n; ++i) {
            dp[i][0] = 1;
        }
        for (int j=1; j<=k; ++j) {
            int l=-1,r=-1;
            for (int i=1; i<=n; ++i) {
                while (l + 1 < i && s[i] - s[l+1] > R) ++l;
                while (r + 1 < i && s[i] - s[r+1] >= L) ++r;
                if (r <= -1) dp[i][j] = 0;
                else dp[i][j] = (dp[r][j-1] - (l==-1?0:dp[l][j-1]) > 0);
            }
            for (int i=1; i<=n; ++i) {
                dp[i][j] += dp[i-1][j];
            }
        }
        return dp[n][k] - dp[n-1][k];    
    };
    int ans = 1e9;
    for (int i=0, j=0; i<d.size(); ++i) {
        while (j<d.size() && !check(d[i].sum, d[j].sum, d[j].l)) ++j;
        if (j==d.size()) break;
        ans = min(ans, d[j].sum - d[i].sum);
    }   
    cout << ans << '\n';
    return 0;
}