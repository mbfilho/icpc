#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
using namespace std;
typedef unsigned long long hash;
typedef long long ll;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define M 150000
#define oo 1000000000

vector<int> adj[M], rev[M];
int f[M];
int n, m;
int r1[M], r2[M];

void dfs(int no, int pai){
	if(r1[no]) return;
	if(f[no] == 1 && pai != -1) return;
	r1[no] = 1;
		
	for( int i = 0; i < adj[no].size(); ++i ){
		int nt = adj[no][i];
		dfs(nt,no);
	}
}

void revDfs(int no){
	if(r2[no]) return;
	r2[no] = 1;
	if(f[no] == 1) return;
	
	for( int i = 0; i < rev[no].size(); ++i ){
		int nt = rev[no][i];
		revDfs(nt);
	}
}


int main(){
	memset( r1, 0, sizeof r1 );
	memset( r2, 0, sizeof r2 );
	
	scanf( "%d %d", &n, &m );
	for( int i = 1; i <= n; ++i ) scanf( "%d", f + i );
	
	for( int i = 0; i < m; ++i ){
		int u, v;
		scanf("%d%d", &u, &v);
		adj[u].pb(v);
		rev[v].pb(u);
	}
	
	for( int i = 1; i <= n; ++i ){
		if(f[i] == 1) dfs(i, -1);
		if(f[i] == 2) revDfs(i);
	}
	
	for( int i = 1; i <= n; ++i ) printf("%d\n", r1[i] * r2[i]);
}

