#include <bits/stdc++.h>
#define fr(i,a,b) for(int i=a;i<b;i++)
#define rep(i,b) fr(i,0,b)

using namespace std;
int n, m;
#define N 300
#define conj kdsjhfsdjf
#define pb push_back

int adj[N][N];
int conj[N];

int find(int a){
	if(conj[a] != a) conj[a] = find(conj[a]);
	return conj[a];
}

int unir(int a, int b){
	conj[find(a)] = find(b);
}

struct E{
	int u, v, c;
};

vector<E> ed;
int faz(){
	random_shuffle(ed.begin(), ed.end());
	rep(i, n) conj[i] = i;
	int qtd = n, prt = 0;
	
	rep(i, ed.size()){
		if(qtd == 2) break;
		
		if(find(ed[i].u) != find(ed[i].v)){
			unir(ed[i].u, ed[i].v);
			--qtd;
			
			if(qtd == 2){
				prt = i+1;
				break;
			}
		}
	}
	
	int resp = 0;
	fr(i, prt, ed.size()){
		if(find(ed[i].u) != find(ed[i].v))
			resp += ed[i].c;
	}
	if(resp == 0) throw 1;
	return resp;
}

int faz2(){
	int resp = 1<<30;
	rep(i, 3*ed.size() + 10) resp = min(resp, faz());
	return resp;
}


char buf[1000];

int mk[N], caso;
void dfs(int no){
	if(mk[no]) return;
	mk[no] = 1;
	
	rep(i, n){
		if(adj[no][i] || adj[i][no]) dfs(i);
	}
}


int main(){
	srand(time(0));
	int caso = 1;
	
	while(scanf("%d%d", &n, &m) == 2){
		ed.clear();
		memset(mk, 0, sizeof mk);
		memset(adj, 0, sizeof adj);
		
		{
			int i = 0;
			while(i < m){
				scanf("%s", buf);
				char* prt = buf;
				int tam = strlen(buf);
				int lidos = 0;
				while(*prt && lidos < tam){
					int u, v, qtd;
					++prt;
					++lidos;
					sscanf(prt, "%d%n", &u, &qtd);
					prt += qtd + 1;
					lidos += qtd + 1;
					sscanf(prt, "%d%n", &v, &qtd);
					adj[min(u, v)][max(u, v)]++;
					prt += qtd + 1;
					lidos += qtd + 1;
					++i;
				}
			}
		}
		
		rep(i, n){
			fr(j, i, n){
				if(adj[i][j]){
					E tmp;
					tmp.u = i;
					tmp.v = j;
					tmp.c = adj[i][j];
					ed.pb(tmp);
				}
			}
		}
		
		dfs(0);
		bool conexo = true;
		rep(i, n){
			if(!mk[i]) conexo = false;
		}
		
		if(n == 0 || n == 1 || !conexo) printf("0\n");
		else printf("%d\n", faz2());
		++caso;
	}	
}



