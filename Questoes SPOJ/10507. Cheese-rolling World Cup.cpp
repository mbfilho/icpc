#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define M 90000
#define N 250
using namespace std;
typedef long long ll;
typedef unsigned long long hash;
#define LEN 30100
#define B 1097

ll hx[N][LEN], rev[N][LEN];
hash pot[LEN];

char nome[N][LEN];
ll pp[N];
ll res[2*M];
ll aux[2*M];
int pred[2*M], adj[2*M], atual[2*M];
int last[N];
ll fluxo[N];
int dist[N];

int cont;
int n, m, k;

void add( int u, int v, ll cap, bool b = true ){
	res[cont] = cap;
	pred[cont] = last[u];
	adj[cont] = v;
	last[u] = cont++;
	
	if(b)
		add(v,u,0,false);
}


char peq( char ch ){
	if( ch >= 'a' && ch <= 'z' ) return ch;
	return ch - 'A' + 'a';
}
 
hash getHx( int no, int ini, int fim ){
	hash tmp = 0;
	if( ini ) tmp = hx[no][ini-1];
	
	return hx[no][fim] - tmp * pot[fim-ini+1];
}

hash getRev( int no, int ini, int fim, int tam ){
	hash tmp = 0;
	if( fim != tam - 1 ) tmp = rev[no][fim+1];
	
	return rev[no][ini] - tmp * pot[fim-ini+1];
}

ll maior[N];

ll dfs( int no, ll menor ){
	if( no == n ) return menor;
	
	ll ret = 0;
	for( int& ed = atual[no]; ed != -1; ed = pred[ed] ){
		int nt = adj[ed];
		if( dist[no] + 1 != dist[nt] || !res[ed] ) continue;
		ret = dfs( nt, min( menor, res[ed] ) );
		if( ret ){
			res[ed] -= ret;
			res[ed^1] += ret;
			return ret;
		}
	}
	
	return ret;
}

bool bfs(){
	memset( dist, -1, sizeof dist );
	for( int i = 0; i <= n; ++i )
		atual[i] = last[i];
		
	queue<int> fila;
	dist[0] = 0;
	fila.push(0);
	bool achou = false;
		
	while( !fila.empty() ){
		int at = fila.front(); fila.pop();
		
		if( at == n ) achou = true;
		for( int ed = last[at]; ed != -1; ed = pred[ed] ){
			if( !res[ed] || dist[adj[ed]] != -1 ) continue;
			dist[adj[ed]] = dist[at] + 1;
			fila.push( adj[ed] );
		}
	}
	return achou;
}


int pvas[N];

int main(){
	pot[0] = 1;
	for( int i = 1; i <= LEN; ++i )
		pot[i] = pot[i-1] * B;
		
	while( scanf( "%d %d %d", &n, &m, &k ) != EOF && (n|m|k) ){
		for( int i = 0; i < n; ++i ){
			scanf( "%s", nome[i] );
			pp[i] = 0;
			
			int tam = strlen(nome[i]);
			hx[i][0] = peq(nome[i][0]);
			rev[i][tam-1] = peq(nome[i][tam-1]);
			// printf( ">>> %s %d\n", nome[i], tam );
			for( int j = 1; j < tam; ++j ){
				hx[i][j] = hx[i][j-1] * B + peq(nome[i][j]);
			}
			
			for( int j = tam - 2; j >= 0; --j ){
				rev[i][j] = rev[i][j+1] * B + peq(nome[i][j]); 
			}
			
			for( int j = 0; j < tam; ++j ){
				int ini = 0, fim = tam, best = -1;
				
				while( ini <= fim ){
					int meio = ( ini + fim ) / 2;
					if( j - meio < 0 || j + 1 + meio >= tam ){
						fim = meio - 1;
						continue;
					}
					
					if( getHx( i, j - meio, j ) == getRev(i, j + 1, j + 1 + meio, tam ) ){
						best = meio;
						ini = meio + 1;
					}else 
						fim = meio - 1;
				}
				
				if( best != -1 ){
					++best;
					pp[i] += (1+best)*best;
				}
			}
			maior[i] = pp[i];
		}
		
		memset( last, -1, sizeof last );
		
		cont = 0;
		for( int i = 0; i < m; ++i ){
			int u,v, c;
			scanf( "%d %d %d", &u, &v, &c );
			add(u,v,c);
		}
		
		sort( maior, maior + n );
		reverse( maior, maior + n );
		int tam = unique(maior, maior+n) - maior;
		
		memcpy( aux, res, sizeof res );
		int sp = 0;
		for( int i = 0; i < n; ++i ){
			fluxo[i] = 0;
			if( pp[i] >= maior[min(k-1, tam-1)] ){
				pvas[sp++] = i;
				if( !i ) continue;
				memcpy( res, aux, sizeof res );
				add(i, n, ll(1e15) );
				ll aum;
				while( bfs() ){
					while( (aum = dfs(0, ll(1e15) ) ) )
						fluxo[i] += aum;
				}
				last[n] = -1;
				last[i] = pred[last[i]];
				cont -= 2;
			}
		}
		
		printf( "%d\n", sp );
		for( int i = 0; i < sp; ++i ){
			printf( "%s (%lld)", nome[pvas[i]], pp[pvas[i]]);
			printf( " %lld\n", fluxo[pvas[i]] );
		}
	}
}





