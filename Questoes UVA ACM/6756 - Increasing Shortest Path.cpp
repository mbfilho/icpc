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

#define N 155
#define K N
#define M 3100
#define oo 1000000000

struct Edge{
	int to, from, cost;
	Edge(){}
	Edge(int u, int v, int c):from(u), to(v), cost(c){}
	bool operator<(const Edge& ot) const{ return cost < ot.cost; }
};

int dist[N][N][N];
int dst, n, m;

Edge graph[M];

void faz(int src, int k){
	rep(i, n) rep(x, k+1) dist[src][i][x] = oo;
	dist[src][src][0] = 0;

	rep(e, m){
		rep(lim, k){
			int to = graph[e].to, from = graph[e].from;
			dist[src][to][lim+1] = min(dist[src][to][lim+1], dist[src][from][lim] + graph[e].cost);
		}
	}

	rep(i, n) fr(lim, 1, k+1) dist[src][i][lim] = min(dist[src][i][lim], dist[src][i][lim-1]);
}

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int q;
		scanf("%d%d%d", &n, &m, &q);
		rep(i, m) scanf("%d%d%d", &graph[i].from, &graph[i].to, &graph[i].cost), --graph[i].to, --graph[i].from;
		sort(graph, graph+m);
		rep(i, n) faz(i, n+1);

		while(q--){
			int a, x;
			scanf("%d%d%d", &a, &dst, &x);
			--a, --dst;
			int ans = dist[a][dst][min(x, n)];
			printf("%d\n", ans == oo ? -1 : ans);
		}
	}
	
	
}
