#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
#define X first
#define Y second
#define mp make_pair
#define N 30000
#define LOG 16

int d[N];
pii fa[N];
vector<int> adj[N];
int qual[N];

struct No{
	int first, second, qual;
	No(){}
	No(int a, int b, int c){
		first = a;
		second = b;
		qual = c;
	}
	
	bool operator<(const No& x) const{
		return first < x.first;
	}
};
vector<No> ed[N];
int start[N], fim[N], tempo;
No dfs(int no, int anc){
	ed[no].clear();
	start[no] = tempo++;
	
	if((adj[no].size() == 1 && adj[no][0] == anc) || !adj[no].size()){
		fim[no] = tempo++;
		return No(0, no, -1);
	}
		
	rep(i, adj[no].size()){
		if(adj[no][i] == anc) continue;
		d[adj[no][i]] = 1 + d[no];
		No tmp = dfs(adj[no][i], no);
		tmp.X++;
		tmp.qual = i;
		ed[no].push_back(tmp);
		fa[adj[no][i]] = mp(no, tmp.Y);
		
		sort(ed[no].begin(), ed[no].end());
		if(ed[no].size() > 2) ed[no].erase(ed[no].begin());
	}
	
	fim[no] = tempo++;
	return ed[no].back();
}

pii indef = mp(-100000,-100000);
pii melhor[N][LOG];
int pai[N][LOG];
int n;

int get(int no){
	int p = fa[no].X, aux = fa[no].Y;
	if(p == -1) return -1;
	
	if(!ed[p].size()) return -1;
	if(ed[p].back().Y != aux) return ed[p].size() - 1;
	return ed[p].size() - 2;
}

void pre(){
	memset(pai, -1, sizeof pai);
	dfs(0, -1);
	fa[0] = mp(-1,-1);
	
	rep(i, n) pai[i][0] = fa[i].X;

	rep(i, n){
		int ind = get(i);		
		melhor[i][0] = indef;
		
		if(~ind){
			int p = fa[i].X;
			melhor[i][0] = mp(ed[p][ind].X - d[p], p);
		}
	}
	for(int tam = 1; (1<<tam) <= n; ++tam){
		rep(i, n){
			if(~pai[i][tam-1]){
				pai[i][tam] = pai[ pai[i][tam-1] ][tam-1];
				melhor[i][tam] = max(melhor[i][tam-1], melhor[ pai[i][tam-1] ][tam-1]);
			}else melhor[i][tam] = indef;
		}		
	}
}

int sobe(int daqui, int tam){
	if(tam < 0) throw 2;
	
	int pot = 0;
	
	while(tam){
		if(tam&1)  daqui = pai[daqui][pot];
		++pot;
		tam >>= 1;
	}
	
	return daqui;
}

pii query(int no, int tam){
	pii best = indef;
	int pot = 0;
	
	while(tam){
		if(tam&1) best = max(best, melhor[no][pot]), no = pai[no][pot];
		if(no == -1)throw 13498;
		++pot;
		tam >>= 1;
	}
	
	return best;
}

int main(){
	int q;
	scanf("%d%d", &n, &q);
	rep(i, n-1){
		int u, v;
		scanf("%d%d", &u, &v);
		--u; --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	pre();
//	printf(">> %d %d\n", ed[0].size(), adj[0].size());
	while(q--){
		int u, k;
		scanf("%d%d", &u, &k);
		--u;
		
		if(ed[u].size() && ed[u].back().X >= k){
			No tmp = ed[u].back();
			printf("%d\n", 1+sobe(tmp.Y, tmp.X - k));
		}else if(d[u] >= k){
			printf("%d\n", 1+ sobe(u, k));
//			printf("aqui2\n");
		}else{
			bool dm = true;
			pii resp = query(u, d[u]);
//			printf("aqui3 %d %d\n", resp.X, resp.Y);
			if(resp != indef && resp.X + d[u] >= k && resp.Y < n && resp.Y >= 0){
				int lcaDist = d[u] - d[resp.Y];
				k -= lcaDist;
				
				int qual = -1;
				for(int i = ed[resp.Y].size() - 1; i>=0; --i){
					int e = ed[resp.Y][i].qual;
					int nt = adj[resp.Y][e];
					if(!(start[nt] <= start[u] && fim[u] <= fim[nt])){
						qual = i;
						break;
					}
				}
//				printf("Qual %d\n", qual);
				if(qual != -1 && qual < ed[resp.Y].size()){
					int folha = ed[resp.Y][qual].Y;
//					printf("Folha %d %d\n", folha, ed[resp.Y][qual].X - k);
					printf("%d\n", 1+sobe(folha, ed[resp.Y][qual].X - k));
					dm = false;
				}
			}
			if(dm)
				printf("0\n");
		}
	}
}









