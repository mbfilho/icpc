#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 1010

int memo[N][N][2], mk[N][N][2], step, n, b;//, jump[N];
char track[N];


int rec(int pos, int bullets, int off = 0){
	// printf("%d %d %d\n", pos, bullets, off);
	if(pos == n - 1) return off ? 2 : 0;

	int& pd = memo[pos][bullets][off];
	if(mk[pos][bullets][off] == step) return pd;
	mk[pos][bullets][off] = step;


	if(off){
		pd = 2 + rec(pos+1, bullets, 1);
		if(track[pos] != '#') pd = min(pd, 2 + rec(pos, bullets, 0));
	}else{
		if(track[pos+1] != '#') pd = 1 + rec(pos+1, bullets, 0);
		else{
			pd = 2 + 2 + rec(pos + 1, bullets, 1);
			if(bullets) pd = min(pd, 1 + rec(pos+1, bullets - 1, 0));
		}
	}
	// printf("(%d,%d,%d): %d\n", pos, bullets, off, pd);

	return pd;
}

int main(){
	int t;
	scanf("%d", &t);
	step = 0;
	memset(mk, 0, sizeof mk);

	while(t--){
		scanf("%d%d%s", &n, &b, track);
		step += 1000;

		printf("%d\n", rec(0, b, 0));

	}
}