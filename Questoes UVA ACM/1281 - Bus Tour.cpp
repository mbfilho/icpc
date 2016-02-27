#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i =a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 20
#define H 18
#define oo 500000000
#define mp make_pair
typedef pair<int,int> pii;

vector<pii> adj[N];
int mk[2][(1<<H) + 5][N], dist[2][(1<<H) + 5][N], n;

struct no{
	int u, v, mask, custo;
	
	no(){}
	no(int a, int mm, int b, int c){
		u = a;
		v = b;
		mask = mm;
		custo = c;
	}
	
	bool operator<(const no& ot) const{
		return !(custo < ot.custo);
	}
};

int caso;
void dij(){
	++caso;
	priority_queue<no> heap;
	rep(i, 2) rep(j, (1<<(n-2))) rep(k, n) dist[i][j][k] = oo;
	
	int s = 0, t = 1;
	int S = 0, T = n-1;
	heap.push(no(s, 0, S, 0)), dist[s][0][S] = 0;
	heap.push(no(t, 0, T, 0)), dist[t][0][T] = 0;
		
	
	while(!heap.empty()){
		no at = heap.top();
		heap.pop();
		
		if(mk[at.u][at.mask][at.v] == caso) continue;
		mk[at.u][at.mask][at.v] = caso;
		
		each(e, adj[at.v]){
			int nt = e -> first, cost = e -> second;
			if(mk[at.u][at.mask][nt] != caso && dist[at.u][at.mask][nt] > at.custo + cost){
				dist[at.u][at.mask][nt] = at.custo + cost;
				heap.push(no(at.u, at.mask, nt, at.custo + cost));
			}
			
			int nmask = at.mask | (1<< (nt-1));
			if(nt > 0 && nt < n - 1 && mk[at.u][nmask][nt] != caso && dist[at.u][nmask][nt] > at.custo + cost){
				dist[at.u][nmask][nt] = at.custo + cost;
				heap.push(no(at.u, nmask, nt, at.custo + cost));
			}
		}
	}
}

int s, t;
int faz(){
	s = 0, t = 1;
	dij();
	int best = oo;
	int h = n - 2;
	rep(mask, (1 << h)){
		if(__builtin_popcount(mask) != h/2) continue;
		int rev = ((1<<h) - 1) & ~mask;
		
		rep(i, n){
			rep(j, n){
//				aproveintando que o grafo eh nao-direcionado 
//				int custo = dist[s][mask][i] + dist[i][rev][t] + dist[t][mask][j] + dist[j][rev][s];
				int custo = dist[s][mask][i] + dist[t][rev][i] + dist[t][mask][j] + dist[s][rev][j];
				best = min(best, custo);
			}
		}
	}
	
	return best;
}

int main(){
	caso = 0;	
	int m;
	while(scanf("%d%d", &n,&m) == 2){
		rep(i, n) adj[i].clear();
		rep(i, m){
			int u, v, t;
			scanf("%d%d%d", &u, &v, &t);
			adj[u].push_back(mp(v,t));
			adj[v].push_back(mp(u,t));
		}
		
		int resp = faz();
		printf("Case %d: %d\n", caso, resp);		
	}
}



