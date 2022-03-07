#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int c;
int q;
int ft[N];
set<int> removed;
set<tuple<int, int, int>> intervals;

void update(int pos, int val){
	while(pos <= n + 1){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int get_sum(int pos){
	int res = 0;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

bool inter(int a, int b, int c, int d){
	return min(b, d) - max(a, c) + 1 > 0;
}

int get_box(int at){
	if(get_sum(at)) return -1;
	set<tuple<int, int, int>>::iterator it = intervals.lower_bound(make_tuple(at, -1, -1));
	if(it != intervals.begin()) it--;
	while(it != intervals.end() and get<0>(*it) <= at){
		int L, R, K;
		tie(L, R, K) = *it;
		if(inter(L, R, at, at)) return removed.count(K) ? -1 : K;
		it++;
	}
	assert(false);
}

void color(int l, int r, int k){
	set<tuple<int, int, int>>::iterator it = intervals.lower_bound(make_tuple(l, -1, -1));
	if(it != intervals.begin()) it--;
	vector<tuple<int, int, int>> to_erase;
	vector<tuple<int, int, int>> to_add;
	int cur_l = -1;
	int cur_r = -1;
	while(it != intervals.end() and get<0>(*it) <= r){
		int L, R, K;
		tie(L, R, K) = *it;
		if(inter(L, R, l, r)){
			to_erase.emplace_back(*it);
			if(!removed.count(K)){
				if(L < l) to_add.emplace_back(make_tuple(L, l - 1, K));
				if(r < R) to_add.emplace_back(make_tuple(r + 1, R, K));

			}
			else{
				update(L, 1);
				update(R + 1, -1);
			}
		}
		it++;
	}
	for(auto e : to_erase) intervals.erase(e);
	for(auto e : to_add) intervals.emplace(e);
	intervals.emplace(make_tuple(l, r, k));
}

int main(){
	scanf("%d %d %d", &n, &c, &q);
	intervals.emplace(make_tuple(1, n, 0));
	for(int s = 1; s <= q; s++){
		char c = getchar();
		while(!isalpha(c)) c = getchar();
		if(c == 'm'){
			int i, j, k;
			scanf("%d %d %d", &i, &j, &k);
			color(i, j, k);
		}
		else if(c == 'b'){
			int k;
			scanf("%d", &k);
			removed.emplace(k);
		}
		else if(c == 'd'){
			int i;
			scanf("%d", &i);
			int box = get_box(i);
			if(box == -1) puts("para que quieres saber eso");
			else if(box == 0) puts("si lo encuentro que te hago");
			else printf("%d\n", box);
		}
		else{
			int i, j;
			scanf("%d %d", &i, &j);
			i = get_box(i); j = get_box(j);
			puts(i == j ? "si" : "no");
		}
	}
	return 0;
}
