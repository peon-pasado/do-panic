---
layout: post
title: problem A.
---


#include <bits/stdc++.h>
using namespace std;

const int maxn = 2510;
bitset<2510> bm[maxn];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    int tc=1;
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) bm[i].reset();
        vector<string> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bm[i][j] = s[i][j] == '1';
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                int r = (bm[i] & bm[j]).count();
                ans += r * (r-1)/2;
            }
        }
        cout << "case " << tc++ << ": " << ans << '\n';
    }
    return 0;
}