#include <cstdio>
#include <queue>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define min(a,b) (a) < (b) ? (a) : (b)
#define N 5000
#define M 2000000

int res[M], pred[M], cont;
int dist[N], last[N], adj[M], atual[N];

int add(int u, int v, int c, int p = 1){
	pred[cont] = last[u];
	last[u] = cont;
	res[cont] = c;
	adj[cont] = v;
	++cont;
	if(p) add(v,u,0,0);
}

bool bfs(int s, int t){
	queue<int> fila;
	rep(i, N) dist[i] = -1, atual[i] = last[i];
	dist[s] = 0;
	int ini = 0, fim = 1;
	fila.push(s);
	
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		for(int e = last[at]; ~e; e = pred[e]){
			int nt = adj[e];
			if((dist[nt] != -1) || (!res[e])) continue;
			dist[nt] = 1 + dist[at];
			if(nt == t) return true;
			fila.push(nt);
		}
	}
	return false;
}

int dfs(int no, int t, int menor){
	if(no == t) return menor;
	
	for(int& e = atual[no]; ~e; e = pred[e]){
		int nt = adj[e];
		if((dist[nt] != 1 + dist[no]) || !res[e]) continue;
		int tmp = dfs(nt, t, min(menor, res[e]));
		if(tmp){
			res[e] -= tmp;
			res[e^1] += tmp;
			return tmp;
		}
	}
	return 0;
}

int maxFlow(int s, int t){
	int flow = 0;
	while(bfs(s,t)){
		int tmp;
		while((tmp = dfs(s,t,100000000))){
			flow += tmp;
		}
	}
	
	return flow;
}


int main(){
	int k, p;
	while(scanf("%d%d", &k, &p) == 2 && (k|p)){
		rep(i, N) last[i] = -1;
		cont = 0;
		
		int soma = 0, s = k+p, t = s+1;
		rep(i, k){
			int c;
			scanf("%d", &c);
			soma += c;
			add(i, t, c);
		}
		rep(i, p){
			int x;
			scanf("%d", &x);
			while(x--){
				int c;
				scanf("%d", &c); --c;
				add(i+k, c, 1);
			}
			add(s, i+k, 1);
		}
		
		if(maxFlow(s,t) == soma){
			printf("1\n");
			rep(i, k){
				bool ft = true;
				for(int e = last[i]; ~e; e = pred[e]){
					int nt = adj[e];
					if(nt != t && !res[e^1]){
						if(!ft) printf(" ");
						else ft = false;
						printf("%d", nt - k + 1);
					}
				}
				printf("\n");
			}
		}else{
			printf("0\n");
		}
	}
}

