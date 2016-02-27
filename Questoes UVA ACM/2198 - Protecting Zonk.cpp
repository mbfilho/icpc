#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,a) Fr(i,0,a)
#define pb push_back
#define N 10100
#define oo 10000000000000LL

vector<int> adj[N];
ll pd[N][5];
int n, c1, c2;
ll choose_general(int no, int pai, int kids_state, int next_state);

#define SOLDIER 0
//colocar o soldier aqui

#define GENERAL 1
//colocar um general

#define ONE 2
//alem dos filhos o vertice tem que cobrir a aresta pro pai

#define LOOSELY 3
//o vertice eh filho de um general

#define TIGHT 4
//as aretas para os filhos desse vertice estao descobertas

ll faz(int no, int pai, int state){
	ll &resp = pd[no][state];
	if(~resp) return resp;
	
	resp = 0;
	
	if(state == SOLDIER){
		resp += c1;
		rep(i, adj[no].size()){
			int nt = adj[no][i];
			if(nt == pai) continue;
			
			resp += faz(nt, no, TIGHT);
		}
	}else if(state == GENERAL){
		resp += c2;
		rep(i, adj[no].size()){
			int nt = adj[no][i];
			if(nt == pai) continue;
			
			resp += faz(nt, no, LOOSELY);
		}
	}else if(state == LOOSELY){
		resp = faz(no, pai, GENERAL);
		ll tmp = 0;
		
		rep(i, adj[no].size()){
			int nt = adj[no][i];
			if(nt == pai) continue;
			
			tmp += faz(nt, no, TIGHT);
		}
		
		resp = min(resp, tmp);
	}else if(state == TIGHT){
		resp = min(faz(no, pai, SOLDIER), faz(no, pai, GENERAL));
		resp = min(resp, choose_general(no, pai, TIGHT, GENERAL));//coloca um general em algum filho
		ll tmp = 0;
		
		rep(i, adj[no].size()){
			int nt = adj[no][i];
			if(nt == pai) continue;
			
			tmp += faz(nt, no, ONE);
		}
		
		resp = min(resp, tmp);
	}else if(state == ONE){
		resp = min(faz(no, pai, SOLDIER), faz(no, pai, GENERAL));
		resp = min(resp, choose_general(no, pai, TIGHT, GENERAL));//coloca um general em algum filho
	}
	
	return resp;
}

ll choose_general(int no, int pai, int kids_state, int next_state){
	ll tmp[N], soma = 0, best = oo;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(nt == pai) continue;
		
		tmp[i] = faz(nt, no, kids_state);		
		soma += tmp[i];
	}
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(nt == pai) continue;
		
		best = min(best, soma - tmp[i] + faz(nt, no, next_state));
	}
	
	return best;
}

int main(){
	while(scanf("%d%d%d", &n, &c1, &c2) == 3 && (n|c1|c2)){
		rep(i,n+1) adj[i].clear();
		
		rep(i, n - 1){
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u].pb(v);
			adj[v].pb(u);
		}
		
		memset(pd, -1, sizeof pd);
		printf( "%lld\n", faz(1, -1, TIGHT));
	}
}


