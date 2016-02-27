#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 2010
#define ft first
#define sd second
typedef pair<int,int> pii;

double memo[N][N];
int n, m;

double rec(int l, int c){
	if(l < 0 || c < 0) return 0;
	if(l == c && l == 0) return 0;
	
	double tot = n * (l + c) - l * c, all = n*n;
	double& pd = memo[l][c];
	if(pd == pd) return pd;
	
	pd = 1 + (l*c/all) * rec(l-1,c-1) + (l*(n-c)/all)*rec(l-1, c) + (c*(n-l)/all)*rec(l, c-1);
	pd /= (1 - (n*n-tot) / all);
	
	return pd;
}

vector<pii> paint;
int main(){
	ios::sync_with_stdio(false);
	
	cin >> n >> m;
	rep(i, m){
		pii tmp;
		cin >> tmp.ft >> tmp.sd;
		paint.push_back(tmp);
	}
	set<int> col, row;
	for(pii par : paint) row.insert(par.ft), col.insert(par.sd);
	
	memset(memo, -1, sizeof memo);
	double ans = rec(n - row.size(), n - col.size());	
	cout << ans << endl;
}
