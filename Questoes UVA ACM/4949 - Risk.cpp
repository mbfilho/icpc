#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 500
#define E (2*N*N)
#define oo 100000000

int value[N];
bool border[N];
int pred[E], adj[E], cap[E], res[E], from[E], cont;
int last[N], atual[N], dist[N];

void add(int u, int v, int c, int p = 1){
	pred[cont] = last[u];
	last[u] = cont;
	adj[cont] = v;
	from[cont] = u;
	cap[cont++] = c;
	if(p) add(v,u,0,0);
}

void popEdge(int edge){
	int u = from[edge];
	if(last[u] != edge) throw 1;
	last[u] = pred[edge]; 
}

int n;

int rebuild(int qtd, int limite, int s, int t){
	while(cont > limite) --cont, popEdge(cont);
	if(last[s] != -1 || last[t] != -1) throw false;
	int necessario = 0;
	
	rep(i, n){
		if(value[i]){
			if(!border[i]) add(s, i, value[i]-1);
			else{
				if(value[i] > qtd){
					add(s, i, value[i]-qtd);
				}
				if(qtd > value[i])
					add(2*n + i, t, qtd - value[i]), necessario += qtd-value[i];
			}
		}
	}
	return necessario;
}

bool bfs(int s, int t){
	rep(i, t+1) atual[i] = last[i], dist[i] = -1;
	queue<int> fila;
	fila.push(s);
	dist[s] = 0;
	
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		
		for(int e = last[at]; ~e; e = pred[e]){
			if(!res[e]){
				continue;
			}
			int nt = adj[e];
			if(~dist[nt]) continue;
			
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
		if(res[e] && dist[nt] == 1 + dist[no]){
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

int maxflow(int s, int t){
	rep(i, cont) res[i] = cap[i];
	int flow = 0;
	
	while(bfs(s,t)){
		int res = 0;
		
		while((res = dfs(s,t,oo)))
			flow += res;
	}
	return flow;
}

char buf[N];
int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		int soma = 0;
		rep(i, n) cin >> value[i], border[i] = false, soma += value[i];
		memset(last, -1, sizeof last);
		cont = 0;
		
		rep(i, n){
			cin >> buf;
			
			if(value[i]){
				rep(j, n){
					if(buf[j] == 'Y'){
						if(value[j]){
							add(n+i, j, oo);
							add(n+i, 2*n+j, oo);
						}else border[i] = true;
					}
				}
				
				add(i, n+i, value[i]);
			}
		}
		
		int s = 3 * n, t = s + 1;
		int ini = 0, fim = soma, limite = cont;
		int resp = -1;
		while(ini <= fim){
			int mid = (ini+fim)/2;
			int necessario = rebuild(mid, limite, s, t);
			int flow = maxflow(s,t);
			if(necessario == flow){
				resp = mid;
				ini = mid + 1;
			}else fim = mid - 1;
		}
		
		cout << resp << endl;
		
	}	
}


