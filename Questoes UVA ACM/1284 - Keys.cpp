#include <bits/stdc++.h>
#define fr(i,a,b) for(int i=a;i<b;i++)
#define rep(i,b) fr(i,0,b)
using namespace std;
#define N 300
#define H 18
#define S 100100
#define mp make_pair
#define ft first
#define sd second
#define oo 100000000
typedef long long ll;
typedef pair<int,int> pii;
#define pb push_back

int mk[N][2], caso, visit[N];
pii pd[N][2];
int setado[N];
vector<int> adj[N];
bool tah[N];

bool chave(int ch){
	return ch >= 'A' && ch <= 'Z';
}

int pega(int ch){
	return (ch >= 'A' && ch <= 'M') ? 0 : 1;
}

pii operator+(pii a, pii b){
	return mp(a.ft + b.ft, a.sd + b.sd);
}

pii rec(int v, int pai, int tpai);

pii calc(int v, int pai, int tpai, int tipo){
	pii resp = mp(0, (tpai != tipo) ? 1 : 0);
	
	rep(i, adj[v].size()){
		int nt = adj[v][i];
		if(nt != pai)
			resp = resp + rec(nt, v, tipo);
	}
	
	return resp;
}
pii indef = mp(oo, oo);

pii rec(int v, int pai, int tpai){
	visit[v] = caso;
	if(chave(v)) return mp(2*(pega(v) != tpai ? 1 : 0), 0);
	
	if(~tpai){
		if(mk[v][tpai] == caso) return pd[v][tpai];
		mk[v][tpai] = caso;
	}

	pii resp = indef;
	
	if(~setado[v]){
		resp = calc(v, pai, tpai, setado[v]);
	}else{
		rep(tipo, 2)
			resp = min(resp, calc(v, pai, tpai, tipo));
	}
	
	if(~tpai) pd[v][tpai] = resp;
	return resp;
}

bool hasKey(int v, int pai = -1){
	if(chave(v)) return true;
	
	rep(i, adj[v].size()){
		int nt = adj[v][i];
		if(nt != pai && hasKey(nt, v)) return true;
	}
	return false;
}

pii rodaPd(){
	++caso;
	pii resp = mp(0,0);
	int roots = 0;

	rep(i, 300){
		if((tah[i] && !chave(i) && visit[i] != caso && hasKey(i)) || ((~setado[i]) && visit[i]!=caso)){
			++roots;
			resp = resp + rec(i, -1, -1);
		}
	}
	resp.sd = 2 * resp.sd - roots;
	return resp;
}

char buf[100];

int main(){
	caso = 0;
	memset(setado, -1, sizeof setado);
	int cas = 0;
	
	while(scanf("%s", buf) == 1){
		rep(i, 300) adj[i].clear(), tah[i] = false;
		int tem[] = {0, 0};
		int aneis = 0;
		
		do{
			rep(i, 2){
				adj[buf[i]].pb(buf[1-i]);
				if(chave(buf[i]) && !tah[buf[i]])
					++tem[pega(buf[i])];
				else if(!tah[buf[i]])
					++aneis;
				tah[buf[i]] = true;
			}
		}while(scanf("%s", buf) == 1 && buf[0] != '0');		
		printf("Case %d: ",  ++cas);
		
		if(tem[0] * tem[1]){
			if(aneis < 2) printf("impossible\n");
			else{
				pii resp = indef;
				rep(i, 300){
					if(!tah[i] || chave(i)) continue;
					setado[i] = 0;
					
					rep(j, 300){
						if(!tah[j] || i == j || chave(j)) continue;
						setado[j] = 1;
						pii tmp = rodaPd();
						resp = min(resp, tmp);
						setado[j] = -1;
					}
					setado[i] = -1;
				}
				printf("%d %d\n", resp.ft, resp.sd - 2);
			}
		}else if(tem[0] + tem[1]){
			pii resp = rodaPd();
			printf("%d %d\n", resp.ft, resp.sd - 1);
		}else printf("0 0\n");
	}
}


