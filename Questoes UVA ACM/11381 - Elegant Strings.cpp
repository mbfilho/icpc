#include <bits/stdc++.h>
using namespace std;
#define maxv 310
#define E 1000000
#define inf 100000000
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
int dist[maxv], pot[maxv], pai[maxv], adj[maxv];
int w[E], ant[E], to[E], cap[E], from[E], cont;

void add(int u, int v, int c, int custo, int p = 1){
	ant[cont] = adj[u];
	adj[u] = cont;
	to[cont] = v;
	from[cont] = u;
	cap[cont] = c;
	w[cont] = custo;
	++cont;
	if(p) add(v, u, 0, -custo, 0);
}

set< pair<int,int> > heap;
void update(int no, int ndist, int p) {
	if(ndist >= dist[no]) return;
	if(dist[no] < inf) heap.erase(pair<int,int>(dist[no],no));
	dist[no] = ndist, pai[no] = p;
	heap.insert(pair<int,int>(dist[no],no)); 
}

pair<int,int> top() {
	pair<int,int> ret = *heap.begin();
	heap.erase(heap.begin());
	return ret; 
}

int djikstra(int source, int sink) {
	heap.clear();
	rep(i, maxv) dist[i] = inf;
	update(source,0,-1);
	while(heap.size()) {
		pair<int,int> p = top();
		for(int i = adj[p.second]; i>=0; i = ant[i]) if(cap[i])
		update(to[i],p.first+w[i]+pot[p.second]-pot[to[i]],i);
	}
	return dist[sink] < inf; 
}
int n;
pair<int,int> mcmf(int source, int sink) {
	memset(pot,0,sizeof pot);
	pair<int,int> p(0,0); // cost,flow
	while(djikstra(source,sink)) {
		int cost = 0, flow = inf;
		for(int x = sink; x != source; x = from[pai[x]])
			if(cap[pai[x]] < flow) flow = cap[pai[x]];
			
		for(int x = sink; x != source; x = from[pai[x]])
			cap[pai[x]] -= flow, cap[pai[x]^1] += flow,
		cost += w[pai[x]]*flow;
		for(int x = 0; x < n; x++) pot[x] += dist[x];
		p.first += cost, p.second += flow;
	}
	return p; 
}

char S[2010], T[200];
int eleg[30][30];

int C(char a){
	return a - 'a';
}

void clear(){
	memset(adj, -1, sizeof adj);
	cont = 0;
	memset(eleg, -1, sizeof eleg);
}

void calc(){
	int tam = strlen(S);
	rep(i, tam-1){
		int a = C(S[i]), b = C(S[i+1]);
		if(eleg[a][b] == -1) eleg[a][b] = (i+1)*(i+1);
	}
}

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		clear();
		scanf("%s %s", S, T);
		calc();
		
		int tam = strlen(T);
		int s = 2 * tam, t = s + 1;
		n = t + 1;
		
		rep(i, tam){
			int u = C(T[i]);
			add(s, i, 1, 0);
			add(i+tam, t, 1, 0);
			
			fr(j, i + 1, tam){
				int v = C(T[j]);
				if(~eleg[u][v]){
					add(i, j + tam, 1, eleg[u][v]);
				}
			}
		}
		
		pair<int,int> resp = mcmf(s,t);
		printf("%d %d\n", tam - resp.second, resp.first);
		
	}
}


