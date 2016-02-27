#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define N 40000
#define M 100000
#define pb push_back
#define mp make_pair

char ma[110][110];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
int n, m;

int comp[N];
int dist[N];
int atual[N];
int last[N];

int pred[M];
int res[M];
int adj[M];
int cap[M];

int num[110][110];

int cont;
bool exc[N];

void add(int u, int v, int c){
	pred[cont] = last[u];
	last[u] = cont;
	cap[cont] = c;
	adj[cont] = v;
	++cont;
}

bool bfs(int s, int t){
	queue<int> fila;
	for(int i = 0; i <= t; ++i){
		dist[i] = -1;
		atual[i] = last[i];
	}
	
	dist[s] = 0;
	fila.push(s);
	
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		
		for(int e = last[at]; ~e; e = pred[e]){
			int nt = adj[e];
			if(~dist[nt] || !res[e]) continue;
			dist[nt] = 1 + dist[at];
			fila.push(nt);
		}
	}
	
	return dist[t] != -1;
}

int dfs(int no, int val, int t){
	if(no == t) return val;
	
	for(int &e = atual[no]; ~e; e = pred[e]){
		int nt = adj[e];
		if(!res[e] || dist[nt] != 1 + dist[no]) continue;
		int tmp = dfs(nt, min(val, res[e]), t);
		if(tmp){
			res[e] -= tmp;
			res[e^1] += tmp;
			return tmp;
		}
	}
	
	return 0;
}

int match(int s, int t){
	int maxFlow = 0;
	
	for(int i = 0; i < cont; ++i) res[i] = cap[i];
	while(bfs(s, t)){
		int tmp;
		while((tmp = dfs(s, 10000000, t))) maxFlow += tmp;
	}
	
	return maxFlow;
}


vector<int> lista;
void undo(int no, int s, int t){
	lista.clear();
	if(comp[no] == 0){
		int at = -1;
		for(int e = last[no]; at == -1 && ~e; e = pred[e]){
			if(!res[e] && adj[e] != s) at = adj[e];
		}
//		printf( "%d >>> [%d]\n",at, adj[at]);
		if(at == -1){
			return;
		}
		for(int e = last[at];~e; e = pred[e]){
			if(adj[e] == t) lista.pb(e);
		}
	}else{
		int at = -1;
		for(int e = last[no]; at == -1 && ~e; e = pred[e]){
			if(res[e] == 1 && adj[e] != t) at = adj[e];
		}
		
		if(at == -1){
			return;
		}
		
		for(int e = last[s]; ~e; e = pred[e]){
			if(adj[e] == at) lista.pb(e);
		}
	}
	
	for(int i = 0; i < lista.size(); ++i){
		int e = lista[i];
		res[e] += 1;
		res[e^1] -= 1;
	}
	if(!lista.size()) throw 1;
//	printf( "%d[%d]\n", lista.size(), comp[no]);
}

void doAgain(){
	for(int i = 0; i < lista.size(); ++i){
		int e = lista[i];
		res[e] -= 1;
		res[e^1] += 1;
	}	
}

int main(){
	while(scanf("%d%d", &n, &m) != EOF && (n|m)){
		for(int i = 0; i < n; ++i) scanf( "%s", ma[i]);
		cont = 0;
		
		int prt = 0;
		int par = 0;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				num[i][j] = prt++;
			}
		}
		comp[0] = 0;
		for(int j = 1; j < m; ++j) comp[num[0][j]] = 1 - comp[num[0][j-1]];
		for(int i = 1; i < n; ++i){
			for(int j = 0; j < m; ++j)
				comp[num[i][j]] = 1 - comp[num[i-1][j]];
		}
		
		int s = prt, t = s + 1;
		for(int i = 0; i <= t; ++i){
			exc[i] = false;
			last[i] = -1;
		}
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(ma[i][j] == 'X') continue;
				if(comp[num[i][j]] == 0){
					add(s, num[i][j], 1);
					add(num[i][j], s, 0);
					for(int k = 0; k < 4; ++k){
						int nx = i + dx[k], ny = j + dy[k];
						if(nx < 0 || nx >= n) continue;
						if(ny < 0 || ny >= m) continue;
						if(ma[nx][ny] == 'X') continue;
						
						add(num[i][j], num[nx][ny], 1);
						add(num[nx][ny], num[i][j], 0);
					}
				}else{
					add(num[i][j], t, 1);
					add(t, num[i][j], 0);
				}

				
			}
		}
		
//		printf( ">%d\n", match(s,t));
//		for(int i = 0; i < n; ++i){
//			for(int j = 0; j < m; ++j){
//				if(ma[i][j] == 'X') continue;
//				int at = num[i][j];
//				for(int e = last[at]; ~e; e = pred[e]){
//					if(!res[e])
//					printf( "%d,%d\n", at, adj[e]);
//				}
//			}
//		}
comp[s] = 2; comp[t] = 3;
for(int i = 0; i < s; ++i){
	for(int e = last[i]; ~e; e =pred[e]){
		if(comp[i] == comp[adj[e]]){
			printf( "%d %d %d\n", i, adj[e], comp[adj[e]]);
			throw 1;
		}
	}
}
		char resp[110][110];
		int a = match(s, t);
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(ma[i][j] == 'X') resp[i][j] = 'X';
				else{
//					exc[num[i][j]] = true;
					undo(num[i][j], s, t);
					if(lista.size() == 0) resp[i][j] = 'B';
					else if(bfs(s,t)) resp[i][j] = 'B';
					else resp[i][j] = 'A';
//					exc[num[i][j]] = false;
					doAgain();
				}
			}
			resp[i][m] = 0;
		}

//	printf( ">> %d\n", cont);		
		for(int i = 0; i < n; ++i) printf( "%s\n", resp[i] );
		printf( "\n");
//		printf( ">>> %d\n", match(s, t));
	}
}





