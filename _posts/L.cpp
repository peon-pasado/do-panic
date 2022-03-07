---
layout: post
title: problem A.
---

#include<bits/stdc++.h>
using namespace::std;

const int MAX = 100000 + 5;

int n;
int k;
int pf[MAX];
int ans[MAX];
int ft[MAX];
vector<int> primes;
bool composite[MAX];
vector<int> values[MAX];

void init(){
	for(int i = 2; i < MAX; i++){
		if(not composite[i]){
			pf[i] = i;
			primes.emplace_back(i);
		}
		for(int p : primes){
			if(i * p >= MAX) break;
			composite[i * p] = true;
			pf[i * p] = max(pf[i], p);
			if(i % p == 0) break;
		}
	}
	for(int i = 2; i < MAX; i++){
		values[pf[i]].emplace_back(i);
	}
}

void update(int pos, int val){
	pos++;
	while(pos < MAX){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int get_sum(int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

void download(int at){
	for(auto x : values[at]) update(x, 1);
}

void solve(vector<pair<int, int>> &queries){
	vector<int> p(queries.size());
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return queries[i].second < queries[j].second;
	});
	int at = 0;
	int l = 0, r = 0;
	while(l < queries.size()){
		while(r < queries.size() and queries[p[l]].second == queries[p[r]].second) r++;
		while(at <= queries[p[l]].second) download(at++);
		for(int i = l; i < r; i++){
			ans[p[i]] = get_sum(queries[p[i]].first);
		}
		l = r;
	}
}

int main(){
	init();
	int t;
	scanf("%d", &t);
	vector<pair<int, int>> queries;
	while(t--){
		scanf("%d %d", &n, &k);
		queries.emplace_back(make_pair(n, k));
	}
	solve(queries);
	for(int i = 0; i < queries.size(); i++) printf("%d\n", ans[i]);
	return 0;
}
