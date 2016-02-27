#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<double,double> Ponto;
#define oo 30000000
#define N 500
#define M 700000
#define X first
#define Y second
#define mp make_pair
#define pb push_back

int cap[M], res[M], pred[M], adj[M];
int last[N], dist[N], atual[N];
int cont;

void add(int u, int v, int c, bool p = true){
	cap[cont] = c;
	pred[cont] = last[u];
	
	last[u] = cont;
	adj[cont] = v;
	++cont;
	
	if(p)
		add(v,u,0,false);
}

Ponto pts[N];
int qtd[N], jumps[N];
int n;
double D;

bool bfs(int s, int t){
	memset(dist, -1, sizeof dist);
	for(int i = 0; i <= 2*n; ++i) atual[i] = last[i];
	
	queue<int> fila;
	fila.push(s);
	dist[s] = 0;
	
	while(!fila.empty()){
		int at = fila.front();
		//printf( "#%d\n", at);
		fila.pop();
		
		for(int e = last[at]; ~e; e = pred[e]){
			int nt = adj[e];
			if(res[e] && dist[nt] == -1){
				dist[nt] = dist[at] + 1;
				
				if(nt == t) return true;
				fila.push(nt);
			}
		}
	}
	return false;
}

int dfs(int no, int t, int menor){
	if(no == t) return menor;
	for(int& e = atual[no]; ~e; e = pred[e]){
		int nt = adj[e];
		//printf( "Nt %d %d %d\n", nt, res[e], dist[e] != dist[no] + 1);
		if(!res[e] || dist[nt] != dist[no] + 1) continue;
		
		int tmp = dfs(nt, t, min(menor, res[e]));
		if(tmp){
			res[e] -= tmp;
			res[e^1] += tmp;
			return tmp;
		}
	}
	
	return 0;
}

int flow(int s, int t){	
	for(int i = 0; i < cont; ++i) res[i] = cap[i];
	int maxFlow = 0;
	
	while(bfs(s,t)){
//		printf("sim\n");

		int f;
		while(1){
			f = dfs(s, t, oo);
			//printf( ">>> %d\n", f);
			if(!f) break;
			maxFlow += f;
		}
		//return 0;
	}
	
	return maxFlow;
}

int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		memset(last, -1, sizeof last);
		cont = 0;
		scanf( "%d %lf", &n, &D);
		int soma = 0;
		for(int i = 0; i < n; ++i){
			scanf("%lf %lf %d %d", &pts[i].X, &pts[i].Y, &qtd[i], &jumps[i]);
			soma += qtd[i];
		}
		
		int s = 2*n;
		for(int i = 0; i < n; ++i){
			add(s, i, qtd[i]);
			add(i, i+n, jumps[i]);
		}
		
		for(int i = 0; i < n; ++i){
			for(int j = i + 1; j < n; ++j){
				Ponto p = mp(pts[j].X - pts[i].X, pts[j].Y - pts[i].Y);
				if(p.X * p.X + p.Y * p.Y <= D * D){
					add(i + n, j, oo);
					add(j+n, i, oo);
				}
			}
		}
		
		
		vector<int> lista;
		for(int i = 0; i < n; ++i){
			int fluxo = flow(s, i);
			if(fluxo == soma) lista.pb(i);
		}
		
		if(!lista.size()) printf( "-1\n");
		else{
			printf( "%d", lista[0]);
			for(int i = 1; i < lista.size(); ++i) printf( " %d", lista[i]);
			printf( "\n");
		}
	}
}


