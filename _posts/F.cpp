---
layout: post
title: problem A.
---


#include<bits/stdc++.h>
using namespace::std;

const int n = 3;

int a[5][5];
char s[5][5];
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};

bool check(int mask){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			a[i][j] = s[i][j] == '*';
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(mask & 1){
				for(int k = 0; k < 5; k++){
					int vx = i + dx[k];
					int vy = j + dy[k];
					if(vx < 0 or vy < 0 or vx >= 3 or vy >= 3) continue;
					a[vx][vy] ^= 1;
				}
			}
			mask >>= 1;
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(a[i][j]) return false;
		}
	}
	return true;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		for(int i = 0; i < 3; i++){
			scanf("%s", s[i]);
		}
		int ans = INT_MAX;
		for(int mask = 0; mask < 1 << 9; mask++){
			if(check(mask)) ans = min(ans, (int)__builtin_popcount(mask));
		}
		printf("%d\n", ans);
	}
	return 0;
}
