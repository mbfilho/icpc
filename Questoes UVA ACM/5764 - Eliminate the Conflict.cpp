#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 20000
#define ROCK 0
#define PAPER 1
#define SCI 2
#define BIG 6*N
#define pb push_back

vector<int> adj[BIG];
int jog[N];
int n, m;

int verd(int a){
	return a * 2;
}

int neg(int a){
	return a * 2 + 1;
}

void add(int a, int b){
	adj[a].pb(b);
	adj[b^1].pb(a^1);
}

int pilha[BIG], sp;
int scc[BIG], tempo[BIG], tmp, comp;

int dfs(int no){
	pilha[sp++] = no;
	int low = tempo[no] = tmp++;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(~scc[nt]) continue;
		if(~tempo[nt]){
			low = min(low, tempo[nt]);
		}else{
			int rec = dfs(nt);
			low = min(low, rec);
		}
	}
	
	if(low == tempo[no]){
		int aux;
		do{
			aux = pilha[--sp];
			scc[aux] = comp;
		}while(aux != no);
		++comp;
	}
	return low;
}

int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int t;
	cin >> t;
	rep(cas, t){
		cin >> n >> m;
		
		rep(i, n){
			rep(j, 3){
				adj[verd(3*i + j)].clear();
				adj[neg(3*i + j)].clear();
			}

			cin >> jog[i];
			--jog[i];
		}
		
		rep(i, m){
			int a, b, k;
			cin >> a >> b >> k;
			--a;
			--b;
			
			if(!k){
				rep(j, 3)
					add(verd(3*a + j), verd(3*b + j));	
			}else{
				rep(j, 3){
					add(verd(3*a + j), neg(3*b + j));
				}
			}
		}
		
		rep(i, n){
			rep(j, 3){
				rep(nt, 3){
					if(j == nt) continue;
					add(verd(3*i + j), neg(3*i + nt));
				}
			}
			
			if(jog[i] == ROCK){
				add(neg(3*i + ROCK), verd(3*i + PAPER));
			}else if(jog[i] == PAPER){
				add(neg(3*i + PAPER), verd(3*i + SCI));
			}else{
				add(neg(3*i + SCI), verd(3*i + ROCK));
			}
		}
		
		sp = tmp = comp = 0;
		memset(scc, -1, sizeof scc);
		memset(tempo, -1, sizeof tempo);
		bool sat = true;
		rep(i, n){
			rep(j, 3){
				if(scc[verd(3*i + j)] == -1){
					sp = 0;
					dfs(verd(3*i + j));
				}
				if(scc[neg(3*i + j)] == -1){
					sp = 0;
					dfs(neg(3*i + j));
				}
				if(scc[neg(3*i + j)] == scc[verd(3*i + j)]){
					sat = false;
					break;
				}
			}
		}
		cout << "Case #" << (cas + 1) << ": ";		
		if(sat)
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
}



