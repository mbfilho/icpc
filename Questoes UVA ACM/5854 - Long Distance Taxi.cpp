#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
#define mp make_pair
#define N 6010
#define K 3010

struct No{
	int at, gas, custo;
	
	void set(int a, int b, int c){
		at = a;
		gas = b;
		custo = c;
	}
	
	bool operator<(const No& a) const{
		return !(custo < a.custo);
	}
};

int dist[N][K], mark[N][K];
int caso = 0;
bool posto[N];
vector<pii> adj[N];
int cap;
No heap[N*K*2];

int faz(int s, int t){
	dist[s][cap*10] = 0;
	int h = 1;
	heap[0].set(s,cap*10,0);
	
	while(h){
		int at = heap[0].at, gas = heap[0].gas, custo = heap[0].custo;
		pop_heap(heap, heap+h);
		--h;
		if(custo > dist[at][gas]) continue;
		if(at == t)
			return custo;
			
		for(int i = 0; i < adj[at].size(); ++i){
			int nt = adj[at][i].first, weight = adj[at][i].second;
			int ngas;
			if(posto[at])
				ngas = cap * 10;
			else
				ngas = gas;
			
			if(ngas < weight) continue;
			ngas -= weight;
			
			if(mark[nt][ngas] != caso || dist[nt][ngas] > custo + weight){
				mark[nt][ngas] = caso;
				dist[nt][ngas] = custo + weight;
				heap[h++].set(nt,ngas,dist[nt][ngas]);
				push_heap(heap, heap + h);
			}
		}
	}
	
	return -1;
}

typedef unsigned long long hash;
map<hash,int> mapa;
int n, m;
char A[100], B[100];

hash giveme(char* arg){
	hash ha = 0;
	for(int i = 0; arg[i]; ++i)
		ha = ha * 1097 + arg[i];
	return ha;
}

int main(){
	memset(mark, 0, sizeof mark);
	map<hash,int>::iterator it;
	
	while(scanf("%d%d%d", &n, &m, &cap) == 3 && (n|m|cap)){
		++caso;
		
		for(int i = 0; i < 2*n; ++i)
			adj[i].clear();
		
		mapa.clear();
		
		int prt = 0, s, t;
		scanf("%s%s", A, B);
		hash ha = giveme(A), hb = giveme(B);
		it = mapa.find(ha);
		if(it == mapa.end())
			s = mapa[ha] = prt++;
		else
			s = it -> second;
		
		it = mapa.find(hb);
		if(it == mapa.end())
			t = mapa[hb] = prt++;
		else
			t = it -> second;
		for(int i = 0; i < n; ++i){
			int u, v, c;
			scanf("%s%s%d", A, B, &c);
			ha = giveme(A);
			hb = giveme(B);
			
			it = mapa.find(ha);
			if(it == mapa.end())
				u = mapa[ha] = prt++;
			else
				u = it -> second;
			
			it = mapa.find(hb);
			if(it == mapa.end())
				v = mapa[hb] = prt++;
			else
				v = it-> second;
			
			adj[u].push_back(mp(v,c));
			adj[v].push_back(mp(u,c));
		}

		
		for(int i = 0; i < prt; ++i)
			posto[i] = false;
			
		for(int i = 0; i < m; ++i){
			int u;
			scanf("%s", A);
			it = mapa.find(giveme(A));
			if(it == mapa.end())
				continue;
				
			u = it -> second;
			posto[u] = true;
		}
		
		int resp = faz(s, t);
		printf("%d\n", resp);	
	}
}










