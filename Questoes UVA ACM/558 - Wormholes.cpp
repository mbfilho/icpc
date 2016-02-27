#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 2000
#define M 3000

int from[M], to[M], w[M], m;
int dist[N], n;

bool bellman(){
	rep(i, n) dist[i] = 1000000000;
	dist[0] = 0;
	rep(i, n) rep(j, m) dist[to[j]] = min(dist[to[j]], dist[from[j]] + w[j]);
	rep(j, m) if(dist[from[j]] + w[j] < dist[to[j]]) return true;
	return false;
}

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d%d", &n, &m);
		rep(i, m) scanf("%d%d%d", from + i, to + i, w + i);
		if(bellman()) printf("possible\n");
		else printf("not possible\n");
	}
}


