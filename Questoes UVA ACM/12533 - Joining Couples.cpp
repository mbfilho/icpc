#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 200000
int ciclo[N], cicIndex[N], root[N], qtd[N], pilha[N], sp, marc[N], level[N];
int cont;

vector<int> adj[N];
int n;
int pai[N][18];

void pre(int x){
	rep(i, x){
		ciclo[i] = root[i] = level[i] = -1;
		marc[i] = 0;
		adj[i].clear();
		
		rep(j, 18)
			pai[i][j] = -1;
	}
	sp = 0;
	cont = 0;
}

void dfs(int no){
	marc[no] = 1;
	pilha[sp++] = no;
	int low = -1;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
//		printf("No %d Nt %d Marc %d\n", no, nt, marc[nt]);
		if(marc[nt] == 0){
			dfs(nt);
		}else if(marc[nt] == 1){
			low = nt;
		}
	}
	
	if(~low){
		int tmp = sp;
		qtd[cont] = 0;
		
		do{
			--tmp;
			ciclo[pilha[tmp]] = cont;
			cicIndex[pilha[tmp]] = qtd[cont]++;
//			printf("Cont %d No %d\n", cont, pilha[tmp]);
		}while(pilha[tmp] != low);
		++cont;
	}
	--sp;
	marc[no] = 2;
}


void pre(){
	queue<int> fila;

	rep(i, n){
		if(~ciclo[i]){
			fila.push(i);
			root[i] = i;
			level[i] = 0;
		}	
	}
	
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		
		rep(i, adj[at].size()){
			int nt = adj[at][i];
			if(ciclo[nt] == -1 && level[nt] == -1){
				root[nt] = root[at];
				pai[nt][0] = at;
				level[nt] = 1 + level[at];
				fila.push(nt);
			}
		}
	}
	
	for(int tam = 1; (1 << tam) <= n; ++tam){
		rep(i, n){
			if(~pai[i][tam-1])
				pai[i][tam] = pai[ pai[i][tam-1] ][tam-1];
		}
	}
}

int query(int u, int v){
	if(level[u] > level[v])
		swap(u,v);
	int dif = level[v] - level[u], pot = 0;
	while(dif){
		if(dif & 1) v = pai[v][pot];
		++pot;
		dif >>= 1;
	}
	
	if(u == v) return v;
	
	pot = 0;
	while((1 << pot) <= n) ++pot;
	--pot;
	
	while(~pot){
		if(pai[u][pot] != pai[v][pot]){
			u = pai[u][pot];
			v = pai[v][pot];
		}
		--pot;
	}
	
	return pai[u][0];
}

int cic(int u, int v){
	int d = abs(cicIndex[u] - cicIndex[v]);
	
	return min(d, qtd[ciclo[u]] - d);
}

int dist(int u, int v){
	if(root[u] == root[v])
		return level[u] + level[v] - 2 * level[query(u,v)];
	if(ciclo[root[u]] == ciclo[root[v]])
		return level[u] + level[v] + cic(root[u], root[v]);
	return -1;
}

int main(){
	while(scanf("%d", &n) == 1){
		pre(n+1);
		rep(i, n){
			int tmp;
			scanf("%d", &tmp);
			adj[tmp-1].push_back(i);
		}
		rep(i, n){
			sp = 0;
			if(!marc[i]) dfs(i);
		}
		
		pre();
		
//		rep(i, n){
//			printf("I %d root %d ciclo %d index %d\n", i, root[i], ciclo[i], cicIndex[i]);
//		}
//		
		int q;
		scanf("%d", &q);
		while(q--){
			int u, v;
			scanf("%d%d", &u, &v);
			--u; --v;
			
			printf("%d\n", dist(u,v));
		}
	}
}





