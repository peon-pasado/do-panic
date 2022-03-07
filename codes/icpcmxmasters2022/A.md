---
layout: page
title: problem A.
---

#include<bits/stdc++.h>
using namespace::std;

int n;
int m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int id(int i, int j){
	return i * (m + 2) + j;
}

int ref(int x){
	return x % 2 == 0 ? 2 - x : 4 - x;
}

int get(int x, vector<int> &par){
	return par[x] == x ? x : par[x] = get(par[x], par);
}

void join(int a, int b, vector<int> &par){
	a = get(a, par);
	b = get(b, par);
	if(a == b) return;
	par[a] = b;
}

int check(int x, int val){
	if(!x) return 0;
	if(val == 0){
		if(x == 1) return true;
		if(x == 5) return true;
		if(x == 6) return true;
		if(x == 7) return true;
		if(x == 11) return true;
		if(x == 13) return true;
		if(x == 14) return true;
		if(x == 15) return true;
		return false;
	}
	else if(val == 1){
		if(x == 2) return true;
		if(x == 5) return true;
		if(x == 8) return true;
		if(x == 9) return true;
		if(x == 11) return true;
		if(x == 12) return true;
		if(x == 14) return true;
		if(x == 15) return true;
		return false;
	}
	else if(val == 2){
		if(x == 3) return true;
		if(x == 6) return true;
		if(x == 8) return true;
		if(x == 10) return true;
		if(x == 11) return true;
		if(x == 12) return true;
		if(x == 13) return true;
		if(x == 15) return true;
		return false;
	}
	else{
		if(x == 4) return true;
		if(x == 7) return true;
		if(x == 9) return true;
		if(x == 10) return true;
		if(x == 12) return true;
		if(x == 13) return true;
		if(x == 14) return true;
		if(x == 15) return true;
		return false;
	}
}

int solve(vector<vector<int>> &v){
	vector<int> par((n + 2) * (m + 2));
	iota(par.begin(), par.end(), 0);
	for(int i = 0; i <= n; i++){
		join(id(i, 0), id(i + 1, 0), par);
		join(id(i, m + 1), id(i + 1, m + 1), par);
	}
	for(int i = 0; i <= m; i++){
		join(id(0, i), id(0, i + 1), par);
		join(id(n + 1, i), id(n + 1, i + 1), par);
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			for(int k = 0; k < 4; k++){
				int i_have = check(v[i][j], k);
				int v_has = check(v[i + dx[k]][j + dy[k]], ref(k));
				if(!i_have and !v_has){
					join(id(i, j), id(i + dx[k], j + dy[k]), par);
				}
			}
		}
	}
	set<int> S;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			S.emplace(get(id(i, j), par));
		}
	}
	return S.size();
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &m, &n);
		vector<vector<int>> v(n + 2, vector<int>(m + 2, 0));
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				scanf("%d", &v[i][j]);
			}
		}
		printf("%d\n", solve(v));
	}
	return 0;
}
