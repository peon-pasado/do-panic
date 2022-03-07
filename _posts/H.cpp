---
layout: post
title: problem A.
---

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int arr[maxn];

int main() {
    int n;
    scanf("%d",&n);
    for (int i = 0; i<n; ++i) {
        scanf("%d", arr+i);
    }
    sort(arr, arr+n);
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        if (sum + 1 < arr[i]) {
            break;
        }
        sum += arr[i];
    }
    cout << sum + 1 << '\n';
    return 0;
}