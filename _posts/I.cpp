---
layout: post
title: problem A.
---

#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> board;

set<board> used;

bool inside(int i, int j, board &a){
	return i >= 0 and j >= 0 and i < a.size() and j < a[0].size();
}

bool check(int x, int y, board &a, board &b){
	for(int i = 0; i < a.size(); i++){
		for(int j = 0; j < a[0].size(); j++){
			int va = a[i][j];
			int vb = inside(x + i, y + j, b) ? b[x + i][y + j] : 1;
			if(va and vb) return false;
		}
	}
	return true;
}

bool search(board &a, board &b){
	int n = a.size(), m = a[0].size();
	for(int i = -n; i < (int)b.size(); i++){
		for(int j = -m; j < (int)b[0].size(); j++){
			if(check(i, j, a, b)) return true;
		}
	}
	return false;
}

void rotate(board &a){
	int n = a.size(), m = a[0].size();
	vector<vector<int>> b(m, vector<int>(n));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			b[i][j] = a[m - j - 1][i];
		}
	}
	a = b;
}

void flip(board &a){
	int n = a.size(), m = a[0].size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m - 1 - j; j++){
			swap(a[i][j], a[i][m - 1 - j]);
		}
	}
}

void solve(board pat, board text){
	queue<board> Q;
	Q.emplace(pat);
	used.emplace(pat);
	bool res = false;
	while(!Q.empty()){
		board u = Q.front(); Q.pop();
		if(search(u, text)){
			res = true;
		}
		for(int i = 0; i < 4; i++){
			rotate(u);
			if(!used.count(u)){
				Q.emplace(u);
				used.emplace(u);
			}
		}
		for(int i = 0; i < 2; i++){
			flip(u);
			if(!used.count(u)){
				Q.emplace(u);
				used.emplace(u);
			}
		}
	}
	puts(res ? "YES" : "IMPOSSIBLE");
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<int>> pat(n, vector<int>(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d", &pat[i][j]);
		}
	}
	scanf("%d %d", &n, &m);
	vector<vector<int>> text(n, vector<int>(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d", &text[i][j]);
		}
	}
	solve(pat, text);
	return 0;
}
