#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 17
typedef pair<int,int> pii;
#define mp make_pair

int pot[N];
int dist[N][1<<N];
pii pai[N][1<<N];
int n, m;
vector<int> adj[N];
int t;

vector<pii> reconstroi(pii estado){
	vector<pii> resp;
	
	do{
		resp.push_back(estado);
		estado = pai[estado.first][estado.second];
	}while(estado != mp(-1,-1));
	
	return resp;
}


vector<pii> bfs(int s, int mask){
	memset(dist, -1, sizeof dist);
	queue<pii> fila;	
	pai[s][mask] = mp(-1,-1);
	dist[s][mask] = 0;
	fila.push(mp(s,mask));
	
	while(!fila.empty()){
		int at = fila.front().first;
		mask = fila.front().second;
		fila.pop();
//		printf("[%d,%d]\n", at, mask);
		
		if(at == t){
//			printf(">>>> %d\n", dist[at][mask]);
			return reconstroi(mp(at,mask));
		}
		
		rep(i, adj[at].size()){
			int nt = adj[at][i];
			if(mask & pot[nt]) continue;
			if(~dist[nt][mask]) continue;
			fila.push(mp(nt, mask));
			pai[nt][mask] = mp(at, mask);
			dist[nt][mask] = 1 + dist[at][mask];
		}
		
		rep(i, n){
			if(pot[i] & mask){
				rep(j, adj[i].size()){
					int nt = adj[i][j];
					if(nt == at) continue;
					if(pot[nt] & mask) continue;
					
					int nmask = (mask ^ pot[i]) | pot[nt];
					if(~dist[at][nmask]) continue;
					fila.push(mp(at,nmask));
					dist[at][nmask] = 1 + dist[at][mask];
					pai[at][nmask] = mp(at, mask);
				}
			}
		}
	}
	return vector<pii>();
}

int main(){
	int casos;
	scanf("%d", &casos);
	rep(i, N) pot[i] = 1<<i;
	
	rep(cas, casos){
		int s;
		scanf("%d%d%d%d", &n, &m, &s, &t);
		--s;
		--t;
		rep(i, n) adj[i].clear();
		int mask = 0;
		
		rep(i, m){
			int tmp;
			scanf("%d", &tmp);
			--tmp;
			mask |= pot[tmp];
		}
		rep(i,n-1){
			int a, b;
			scanf("%d%d", &a, &b);
			--a; --b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		
		vector<pii> resp = bfs(s, mask);
		printf("Case %d: %d\n", cas + 1, resp.size() - 1);
		while(resp.size() > 1){
			pii ft = resp.back();
			resp.pop_back();
			pii snd = resp.back();
			
			if(ft.first != snd.first) printf("%d %d\n", ft.first+1, snd.first+1);
			else{
				int mask = ft.second ^ snd.second;
				int ini = ft.second & mask;
				rep(i, n){
					if(pot[i] & ini){
						printf("%d", i + 1);
						break;
					}
				}
				int fim = mask & snd.second;
				rep(i, n){
					if(pot[i] & fim){
						printf(" %d\n", i + 1);
						break;
					}
				}
			}
		}
		printf("\n");

	}
}

