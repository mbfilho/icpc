#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 10100
#define M 2*N
#define pb push_back
#define mp make_pair
#define LOG 16
typedef long long ll;
typedef pair<int,int> pii;

int to[M], from[M], pred[M], edges;
int last[N];

inline void add(int u, int v, int p = 1){
	to[edges] = v;
	from[edges] = u;
	pred[edges] = last[u];
	last[u] = edges++;

	if(p) add(v,u,0);
}

int pai[N], tree[N], level[N], in[N], out[N];
int tempo;

int dfs(int no, int p, int lvl){
	pai[no] = p;
	level[no] = lvl;
	tree[no] = 1;
	in[no] = tempo++;
	
	for(int e = last[no]; ~e; e = pred[e]){
		int nt = to[e];
		if(nt != p)
			tree[no] += dfs(nt, no, lvl+1);
	}
	out[no] = tempo++;
	
	return tree[no];
}

struct no{
	vector<int> maior, esq, dir;
	int prt, n;
	
	void init(int size){
		prt = 0;
		n = size;
		maior = vector<int>(2*size - 1, -1);
		esq = vector<int>(2*size - 1, -1);
		dir = vector<int>(2*size - 1, -1);
		build(prt++, 0, size-1);
	}
	
	int build(int no, int ini, int fim){
		if(ini != fim){
			int mid = (ini+fim)/2;
			esq[no] = build(prt++, ini, mid);
			dir[no] = build(prt++, mid+1, fim);
		}
		return no;
	}
	
	void insert(int no, int ini, int fim, int val, int ind){
		if(ind < ini || ind > fim) return;
		int mid = (ini+fim)/2;
		
		if(ini == fim && ini == ind)
			maior[no] = val;
		else if(~esq[no]){
			insert(esq[no], ini, mid, val, ind);
			insert(dir[no], mid+1, fim, val, ind);
			
			maior[no] = max(maior[dir[no]], maior[esq[no]]);
		}
		
	}
	void insert(int val, int ind){
		insert(0, 0, n-1, val, ind);
	}
	
	int query(int no, int ini, int fim, int x, int y){
		if(x > fim || y < ini) return -1;
		if(x <= ini && y >= fim) return maior[no];
		int mid = (ini+fim)/2;
		
		return max(query(esq[no], ini, mid, x, y), query(dir[no], mid+1, fim, x, y));
	}
	int query(int ini, int fim){
		return query(0, 0, n-1, ini, fim);
	}
	
}nos[N];

vector<int> paths[N];
int pathId[N];
int pathIndex[N];
int path;

int pilha[N], sp;
void heavy(int no, bool way){
	bool head = false;
	if(way) pilha[sp++] = no;
	
	for(int e = last[no]; ~e; e = pred[e]){
		int nt = to[e];
		if(nt != pai[no]){
			bool isHeavy = 2*tree[nt] >= tree[no];
			if(isHeavy && !way){
				pilha[sp++] = no;
				head = true;
			}
			heavy(nt, isHeavy);
		}
	}
	
	if(head){
		int tmp;
		int cnt = 0;
		do{
			tmp = pilha[--sp];
			paths[path].pb(tmp);
			pathId[tmp] = path;
			pathIndex[tmp] = cnt++;
		}while(tmp != no);
		nos[path].init(cnt);
		++path;
	}
}

int n;

inline bool ehAnc(int pai, int filho){
	return in[pai] <= in[filho] && out[pai] >= out[filho];
}

inline int ajeita(int p, int root = 0){
	if(p == -1) return root;
	return p;
}

int lca(int u, int v, int root = 0){
	
	while(1){
		if(ehAnc(u,v)) return u;
		if(ehAnc(v,u)) return v;
		int nu = ajeita(pai[u], root), nv = ajeita(pai[v], root);
		
		if(~pathId[u]) nu = ajeita(pai[paths[pathId[u]].back()]);
		if(~pathId[v]) nv = ajeita(pai[paths[pathId[v]].back()]);
		
		if(level[nu] < level[nv]) v = nv;
		else u = nu;
	}
}

void clear(int n = N){
	sp = path = edges = tempo = 0;
	
	rep(i, n){
		last[i] = -1;
		pathId[i] = -1;
		paths[i].clear();
	}
}

pii arestas[M];
int val[N];

int calc(int u, int anc){
	int resp = -1;
	
	while(u != anc){
		if(pathId[u] == -1){
			resp = max(resp, val[u]);
			u = pai[u];
		}else{
			int p = pathId[u];
			int nt = paths[p].size() - 1;
			if(pathId[anc] == p)
				nt = pathIndex[anc] - 1;
			resp = max(resp, nos[p].query(pathIndex[u], nt));
			u = pai[paths[p][nt]];
		}
	}
	
	return resp;
}

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d", &n);
		clear(n);
		rep(i, n-1){
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			--u;--v;
			arestas[i] = mp(edges, c);
			add(u,v);
		}
		
		dfs(0,-1, 0);
		heavy(0, false);

		rep(i,n-1){
			int e = arestas[i].first, no;
			if(level[to[e]] < level[from[e]]) no = from[e];
			else no = to[e];
			val[no] = arestas[i].second;
			
			if(~pathId[no])
				nos[pathId[no]].insert(val[no], pathIndex[no]);
		}
		
		char op[10];
		while(scanf("%s", op) == 1 && op[0] != 'D'){
			if(op[0] == 'Q'){
				int u, v, anc;
				scanf("%d%d", &u, &v);
				--u; --v;
				anc = lca(u,v);
				int maior = max(calc(u, anc), calc(v, anc));
				printf("%d\n", maior);				
			}else{
				int e, c;
				scanf("%d%d", &e, &c);
				e = arestas[e-1].first;
				
				int u = to[e], v = from[e];
				int no;
				if(level[u] < level[v]) no = v;
				else no = u;
				
				if(pathId[no] == -1) val[no] = c;
				else{
					int p = pathId[no], ind = pathIndex[no];
					nos[p].insert(c, ind);
				}
			}
		}
	}
}

