#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
#define M N

int con[N+M], indice[N], soma[N+M], qtd[N+M];
int n, m;

void make_set(){
	rep(i, n+m+5) con[i] = i, soma[i] = 0, qtd[i] = 0;

	rep(i,n+1) qtd[i] = 1, soma[i] = i, indice[i] = i;
}

int find(int u){
	if(con[u] != u) con[u] = find(con[u]);
	return con[u];
}

void unir(int u, int v){
	soma[find(v)] += soma[find(u)];
	qtd[find(v)] += qtd[find(u)];
	con[find(u)] = find(v);
}

int prt;
void destacar(int src, int dest){
	soma[find(indice[src])] -= src;
	--qtd[find(indice[src])];
	indice[src] = prt;
	
	++qtd[prt];
	soma[prt] += src;
	
	unir(prt, indice[dest]);
	++prt;
	
}

int main(){
	while(scanf("%d%d", &n, &m) == 2){
		make_set();
		prt = n+1;
		while(m--){
			int op;
			scanf("%d", &op);
			if(op == 1){
				int p, q;
				scanf("%d%d", &p, &q);
				if(find(indice[p]) != find(indice[q]))
					unir(indice[p], indice[q]);
			}else if(op == 2){
				int dest, src;
				scanf("%d%d", &src, &dest);
				
				if(find(indice[src]) != find(indice[dest]))
					destacar(src, dest);
			}else{
				int p;
				scanf("%d", &p);
				p = find(indice[p]);
				printf("%d %d\n", qtd[p], soma[p]);
			}
		}
	}	
}

