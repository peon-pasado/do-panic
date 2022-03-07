---
layout: post
title: problem A.
---


#include<bits/stdc++.h>
using namespace::std;

int n;
int m;
int cnt;
int last;
int last_zero;

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		int cur = last_zero < i - m ? 0 : 1;
		last = cur;
		if(__builtin_popcount(i) & 1) cur = 1;
		if(cur == 0) last_zero = i;
	}
	puts(last ? "Pay the bill" : "Free snacks!");
	return 0;
}
