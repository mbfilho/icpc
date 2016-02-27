#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
#define N 15

int pot[N];
int adj[N];

int grupo[N], conj[N];
int str;

bool achou;
bool clique;
bool consistente[1<<N];

int a, b, n;
int comb[N];

void findClique(int* graph, int k){
	memset(comb, 0, sizeof comb);
	for(int i = k, j = a; j > 0; --j, --i ){
		comb[i] = 1;
	} 
	
	do{
		int nos = 0;
		bool dm = false;

		for( int i = 1; i <= k; ++i ){
			if(comb[i]) nos |= pot[i];
		}
		
		for(int i = 1; !dm && i <= k; ++i ){
			int tmp = nos & (~pot[i]);
			int tmp2 = graph[i] & (~pot[i]);
			if(comb[i] && (tmp2 & tmp) != tmp ) dm = true;
		}
		if(!dm){
			achou = true;
			return;
		}
		
	}while( next_permutation(comb + 1, comb + k + 1) );

}

void findBipartite(int* graph, int k){
	memset(comb, 0, sizeof comb);
	int c = min(a,b);
	for( int i = k, j = c; j > 0; --i, --j ){
		comb[i] = 1;
	}
	
	do{
		int nos = -1;
		int part = 0;
		bool dm = false;
		
		for( int i = 1;i <= k; ++i ){
			if(comb[i])	part |= pot[i];
		}
		
		for(int i = 1; i <= k; ++i ){
			if(comb[i])
				nos &= (graph[i] & (~part));
		}
		if(__builtin_popcount(nos) >= max(a,b)){
			achou = true;
			return;
		}
	}while(next_permutation(comb + 1, comb + k + 1));
}

int errados;
int h;
void testar(int k){
	int graph[N];
	memset(graph, 0, sizeof graph);
	
//	int cnt = 0;
//	int h;
//	for( int i = 1; i <= k; ++i ){
//		if(!grupo[i]) throw 1;
//		if(!consistente[grupo[i]]){
//			h = i;
//			++cnt;
//		}
//	}
//	
//	if( cnt > errados ) return;
	
	for( int i = 1; i <= n; ++i ){
		for( int j = 1; j <= n; ++j ){
			if( (adj[i] & pot[j]) ){
				graph[conj[i]] |= pot[conj[j]];
			}
		}
	}
	
	if(~h){
		for( int i = 1; i <= k; ++i ){
			graph[i] &= (~pot[h]);
		}
		graph[h] = 0;
	}

	
	if(clique) findClique(graph, k);
	else findBipartite(graph, k);
}

void contraction(int x, int k, int g){
	if(!k && !x){
		testar(g);
		return;
	}
	
	if(!x) return;
	if(!k) return;
	if(x < k) return;
	
	if(x != k){
		for(int i = k; i > 0; --i){
			grupo[i] |= pot[x];
			conj[x] = i;
			contraction(x-1,k, g);
			if(achou) return;
			grupo[i] ^= pot[x];
		}
	}
	
	grupo[k] |= pot[x];
	conj[x] = k;

	if(consistente[grupo[k]])
		contraction(x-1,k-1,g);
	else if(errados){
		h = k;
		errados = 0;
		contraction(x-1,k-1,g);
		errados = 1;
		h = -1;
	}
	
	grupo[k] ^= pot[x];
}

char buf[200];

int mark;
void dfs(int mask, int no){
	if(!(mask & pot[no])) return;
	if(mark & pot[no]) return;
	mark |= pot[no];
	
	for( int i = 1; i <= n; ++i ){
		if(adj[no] & pot[i])
			dfs(mask, i);
	}
}

int main(){
	pot[0] = 1;
	for( int i = 1; i < N; ++i ) pot[i] = 2 * pot[i-1];
	int caso = 0;
	while(scanf("%d", &n) != EOF && n){
		caso++;
		
		memset( grupo, 0, sizeof grupo );
		a = b = -1;
		
		scanf( "%s", buf );
		char* tmp = buf + 1;
		int qtd;
		sscanf(tmp, "%d%n", &a, &qtd);
		tmp += qtd;
		if(*tmp){
			++tmp;
			clique = false;
			sscanf(tmp, "%d", &b );
		}else
			clique = true;
		
		for(int i = 1; i <= n; ++i ){
			adj[i] = 0;
			for( int j = 1; j <= n; ++j ){
				int c;
				scanf( "%d", &c );
				if(c) adj[i] |= pot[j];
			}
		}
		
		for(int i = 1; i < pot[n]; ++i){
			int mask = i << 1;
			for( int j = 1; j <= n; ++j ){
				if(mask & pot[j]){
					mark = 0;
					dfs(mask, j);
					consistente[mask] = (mark == mask);
					break;
				}
			}
		}
		achou = false;
		errados = 0;
		int vertices = a;
		if(!clique) vertices += b;
		
		h = -1;
		if(vertices <= n)
			contraction(n, vertices, vertices);
		if(!achou && vertices + 1 <= n){
			errados = 1;
			contraction(n, vertices+1, vertices+1);
		}
		
		if(achou) printf("Case %d: Found\n",caso);
		else printf("Case %d: Not found\n",caso);
	}
}

