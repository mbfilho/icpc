#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N (51*51)
#define M (80*N)

char ma[60][60];
int pred[M], adj[M], res[M], cont;
int last[N], atual[N], dist[N];

void add(int u, int v, int c, int p = 1){
	adj[cont] = v;
	pred[cont] = last[u];
	last[u] = cont;
	res[cont] = c;
	++cont;
	if(p) add(v,u,c,0);
}

bool bfs(int s, int t){
	memset(dist, -1, sizeof dist);
	rep(i, N) atual[i] = last[i];
	
	queue<int> fila;
	dist[s] = 0;
	fila.push(s);
	
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		
		for(int e = last[at]; ~e; e = pred[e]){
			int nt = adj[e];
			if(res[e] && dist[nt] == -1){
				dist[nt] = 1 + dist[at];
				if(nt == t) return true;
				fila.push(nt);
			}
		}
	}
	
	return false;
}

int dfs(int at, int t, int menor){
	if(at == t) return menor;
	
	for(int& e = atual[at]; ~e; e = pred[e]){
		int nt = adj[e];
		if(dist[nt] == 1 + dist[at] && res[e]){
			int tmp = dfs(nt, t, min(menor, res[e]));
			if(tmp){
				res[e] -= tmp;
				res[e^1] += tmp;
				return tmp;
			}
		}
	}
	
	return 0;
}

int maxFlow(int s, int t){
	int flow = 0;
	
	while(bfs(s,t)){
		int resp = 0;
		
		while((resp = dfs(s,t, 0x7fffffff))) flow += resp;
	}
	
	return flow;
}

int n, m;
int get(int i, int j){
	return i * m + j;
}

int main(){
	
	while(scanf("%d%d", &n, &m) == 2){
		rep(i, n) scanf("%s", ma[i]);
		cont = 0;
		memset(last, -1, sizeof last);
		
		int A = 0, B = 0;
		int s = get(n-1,m-1) + 1, t = s + 1;
		
		int dx[] = {1, 0}, dy[] = {0, 1};
		rep(i, n){
			rep(j, m){
				if(ma[i][j] != '.') continue;
				if((i+j)%2 == 0){
					++A;
					add(s, get(i,j), 1);
				}else{
					++B;
					add(get(i,j), t, 1);
				}
				
				rep(k, 2){
					int ni = i + dx[k], nj = j + dy[k];
					if(ni >= 0 && ni < n && nj >= 0 && nj < m && ma[ni][nj] == '.')
						add(get(i,j), get(ni,nj), 1);	
				}
			}
		}
		
		if(A == B && maxFlow(s,t) == A) printf("2\n");
		else printf("1\n");
	}
}





