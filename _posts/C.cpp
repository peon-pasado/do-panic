---
layout: post
title: problem A.
---


#include<bits/stdc++.h>
using namespace::std;

const long double EPS = 1e-10;

const string name[] = {"name", "uom", "value"};

string s;

vector<string> split(string s, char sep = ','){
	int l = 0, r;
	vector<string> res;
	while(l < s.size()){
		r = l;
		string cur = "";
		while(r < s.size() and s[r] != sep){
			cur.push_back(s[r]);
			r++;
		}
		res.emplace_back(cur);
		l = r + 1;
	}
	return res;
}


long double get_val(string s){
	long double num = 0;
	long double den = 1;
	bool mul_den = false;
	for(int i = 0; i < s.size(); i++){
		if(s[i] == '.'){
			mul_den = true;
			continue;
		}
		num = 10 * num + s[i] - '0';
		if(mul_den) den *= 10;
	}
	return num / den;
}

string check(string a, string b, string c){
	long double A = get_val(a), B = get_val(b), C = get_val(c);
	return A - EPS <= C and C <= B + EPS ? "PASS" : "FAIL";
}

int main(){
	getline(cin, s);
	puts("<root>");
	puts("<serialnumber>");
	printf("%s\n", s.c_str());
	puts("</serialnumber>");
	vector<vector<string>> measures;
	while(getline(cin, s)){
		measures.emplace_back(split(s));
	}
	if(!measures.empty()){
		puts("<measures>");
		for(auto v : measures){
			cout << "<measure";
			for(int i = 0; i < 3; i++){
				cout << " " << name[i] << "=\"" << v[i] << "\""; 
			}
			cout << " status=\"" << check(v[3], v[4], v[2]) << "\"></measure>\n";
		}
		puts("</measures>");
	}
	puts("</root>");
	return 0;
}
