#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 110
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,a) Fr(i,0,a)

int n, m;
bool reach[N][N];
bool adj[N][N];
int comp[N], marc[N], pilha[N], tempo[N], sp, tmp, cont;
int nos[N], ord[N], indice;
int resp;

int dfs(int no){
	int menor = tempo[no] = tmp++;
	pilha[sp++] = no;
	marc[no] = true;
	
	rep(i,n){
		if(!adj[no][i]) continue;
		if(~comp[i]) continue;

		if(marc[i]) menor = min(menor, tempo[i]);
		else{
			menor = min(menor, dfs(i));
		}
	}
	
	if(menor == tempo[no]){
		int aux, qtd = 0;
		
		do{
			aux = pilha[--sp];
			comp[aux] = cont;
			++qtd;
		}while(aux != no);
		nos[cont++] = no; //representante do componentes fortemente conexo
	
		if(qtd > 1)
			resp += qtd;
	}
	
	return menor;
}

void topo(int no){
	marc[no] = true;
	
	for(int i = 0; i < cont; ++i){
		int nt = nos[i];
		if(!adj[no][nt]) continue;
		if(marc[nt]){
			continue;
		}
		if(comp[no] == comp[nt]){
			throw 1;
			continue;
		}
		
		topo(nt);	
	}
	ord[indice++] = no;
}

void faz(){
	memset(reach, false, sizeof reach);
	
	for(int i = 0; i < cont; ++i){
		int at = ord[i];
		for(int j = i - 1; ~j; --j){
			int prev = ord[j];
			if(reach[prev][at]) continue;
			if(adj[prev][at]){
				++resp;
				reach[prev][at] = true;
				
				rep(a,cont)
					reach[ord[a]][at] |= reach[ord[a]][prev];
			}
		}
	}
}

int main(){
	int caso = 1;
	while(scanf("%d%d", &n, &m) == 2 && (n|m)){
		cont = resp = indice = tmp = 0;
		memset(comp, -1, sizeof comp);
		memset(adj, false, sizeof adj);
		rep(j, m){
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u-1][v-1] = true;
		}

		rep(k,n){
			rep(i,n){
				rep(j,n){
					if(i == j){
						adj[i][i] = false;
						continue;
					}
					adj[i][j] |= (adj[i][k] && adj[k][j]);
				}
			}
		}
		
		memset(marc, false, sizeof marc);
		rep(i, n){
			if(!marc[i]){
				sp = 0;
				dfs(i);
			}
		}
				
		memset(marc, false, sizeof marc);
		rep(i, cont){
			bool ehRoot = true;
			rep(j,cont){
				if(i != j && comp[nos[j]] == comp[nos[i]]) throw 2;
				if(adj[nos[j]][nos[i]]){
					ehRoot = false;
					break;
				}
			}
			if(ehRoot && marc[nos[i]]) throw 1;
			if(ehRoot){
				topo(nos[i]);
			}
		}
		reverse(ord, ord + cont);
		faz();
		printf( "Case %d: %d\n", caso++, resp);
		
	}
}






