#include <algorithm>
#include <cstdio>
#include <stack>
#include <cstring>
#include <vector>
#define fr(i,a,b) for(int i=a;i<b;i++)
#define rep(i,b) fr(i,0,b)
using namespace std;
#define N 200
#define E 210*210
#define oo 100000000
int value[E];
int pai[E], ord[E], low[E], ant[E], adj[E], markv[E], marke[E], to[E], from[E];
int edges, nbc, tempo;
int pilha[E], q;
int soma[E];
int cmp[E];

void add(int u, int v, int p = 1){
	ant[edges] = adj[u];
	adj[u] = edges;
	to[edges] = v;
	from[edges] = u;
	++edges;
//	
	if(p) add(v,u, 0);
}

 
#define PB push_back
void gerar(int no){
	vector<int> vet;
	while(q--){
		vet.push_back(from[pilha[q]]);
		vet.push_back(to[pilha[q]]);
		if(from[pilha[q]] == no) break;
	}
	
	if(vet.size() > 2){
		sort(vet.begin(), vet.end());
		int tam = unique(vet.begin(), vet.end())-vet.begin();
		soma[nbc] = 0;
		rep(i, tam){
			int no2 = vet[i];
			cmp[no2] = nbc;
			soma[nbc] += value[no2];
		}
		++nbc;
	}
}


void dfs(int no, int dad){
	pai[no] = dad, ord[no] = low[no] = tempo++;
	markv[no] = 1;
	
	for(int i = adj[no]; i >= 0; i = ant[i]){
		int prox = to[i];
		if(!marke[i]){
			marke[i] = marke[i^1] = 1;
			pilha[q++] = i;
		}
		if(!markv[prox]){
			dfs(prox, no);
			low[no] = min(low[no], low[prox]);
		}else if(prox != dad){
			low[no] = min(low[no], ord[prox]);
		}
		
		if(q && pai[prox] == no && low[prox] >= ord[no]){
			gerar(no);
		}
	}
}


int B[N];
int t, n, m, b;
int pd[N][N];

int memo(int cn, int cb){
	if(cn > cb) return oo;
	if(cn < 0) return -oo;
	
	int& rec = pd[cn][cb];
	if(~rec) return rec;
	
	rec = min(memo(cn,cb-1), max(abs(soma[cn] - B[cb]), memo(cn-1, cb-1)));
	return rec;
}


int main(){
	scanf("%d", &t);
	
	rep(cas, t){
		scanf("%d%d%d", &n, &m, &b);
//		if(b > 50) throw 1; pen!
		memset(marke, 0, sizeof marke);
		rep(i, n){
			scanf("%d", value + i);
			adj[i] = -1;
			markv[i] = 0;
			cmp[i] = -1;
		}
		rep(i, b) scanf("%d", B + i);
		
		tempo = 0;
		edges = 0;
		nbc = 0;
		while(m--){
			int u, v;
			scanf("%d%d", &u, &v);
			--u; --v;
			add(u,v);
		}
		
		rep(i, n){
			if(!markv[i]) dfs(i, -1);
			if(cmp[i] == -1){
				soma[nbc++] = value[i];
			}
		}
		
		printf("Buzz Mission %d: %d", cas+1, nbc);
		if(nbc > b) puts(" No");
		else{
			sort(soma, soma + nbc);
			sort(B, B + b);
			memset(pd, -1, sizeof pd);
			int custo = memo(nbc-1, b-1);
			printf(" %d\n", custo);
		}
	}
}


