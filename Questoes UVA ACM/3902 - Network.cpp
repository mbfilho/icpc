#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 2000
typedef pair<int,int> pii;
#define mp make_pair
#define X first
#define Y second
#define oo 2000

int uncover[N];
vector<int> adj[N];
int s, k, n;

void dfs(int no, int pai, int d){
	if(adj[no].size() == 1){
		uncover[no] = (d > k);
		return;
	}
	uncover[no] = 0;
	
	for(int i = 0; i < adj[no].size(); ++i){
		int nt = adj[no][i];
		if(nt == pai) continue;
		
		dfs(nt, no, d + 1);
	}
}

int resp;
pii dfs(int no, int pai){
	if(adj[no].size() == 1){
		int ret;
		if(uncover[no]) ret = 0;
		else ret = -1;
		// printf( "Folha %d: %d\n", no, ret);
		
		return mp(ret, oo);
	}

	int maior = -1;
	int server = oo;
	for(int i = 0; i < adj[no].size(); ++i){
		int nt = adj[no][i];
		if(nt == pai) continue;
		
		pii rec = dfs(nt, no);
		maior = max(maior, rec.X);
		server = min(server, rec.Y);
	}
	
	if(server + 1 + maior + 1 <= k) return mp(-1, server + 1);
	
	if(maior == -1){
		// printf( "Interno %d: oo\n", no);
		return mp(maior, server + 1);
	}
	
	if(maior + 1 < k){
		// printf( "Interno %d: %d\n", no, maior + 1);
		return mp(maior + 1, server);
	}
	else{
		++resp;
		// printf( "Interno %d: oo [build]\n", no);
		return mp(-1, 0);
	}
}


int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d%d%d", &n, &s, &k);
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
		
		for(int i = 1; i < n; ++i){
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
		dfs(s, -1, 0);
		resp = 0;
		dfs(s,-1);
		printf("%d\n", resp);
	}
}


