#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;

#define fr(i,a,b) for(int i=a;i<b;++i)
#define rep(i,n) fr(i,0,n)
#define N 60
#define mp make_pair
#define oo 100000000
#define T 1000000
typedef pair<int,int> pii;
#define F first
#define S second

int mk[N*N];
vector<int> adj[N];
int atual[N];
pii edges[N*N];

int pegaAdj(int no, int e){
	if(edges[e].F == no) return edges[e].S;
	return edges[e].F;
}

int cnt;

void dfs(int no){
	while(atual[no] < adj[no].size()){
		int e = adj[no][atual[no]++];
		if(~mk[e]) continue;
		mk[e] = cnt++;
		
		int nt = pegaAdj(no, e);
		dfs(nt);
	}
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	int tmp = 0;
	
	rep(i, m){
		int u, v;
		scanf("%d%d", &u, &v);
		adj[u].push_back(i);
		adj[v].push_back(i);
		edges[i] = mp(u,v);
		mk[i] = -1;
	}
	rep(i, n) atual[i] = 0;
	cnt = 1;
	dfs(1);
	printf("YES\n");
	rep(i, m){
		if(i) printf(" ");
		printf("%d", mk[i]);
	}
	printf("\n");
}







