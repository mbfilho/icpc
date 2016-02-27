#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;


#define N 2001
#define M 3001
#define oo 500000000

int last[ N ], pred[ M ], adj[ M ], peso[ M ], cont, n, m, ft[ M ];
int pilha[ N ], sp;
int dist[ N ];
bool marc[ N ];

void add( int u, int v, int p ){
	pred[ cont ] = last[ u ];
	last[ u ] = cont;
	adj[ cont ] = v;
	ft[ cont ] = u;
	peso[ cont ] = p;
	++cont;
}

int tempo[ N ], low[ N ], contador, scc, comp[ N ], qtd[ N ];
void dfs( int no ){
	marc[ no ] = true;
	tempo[ no ] = low[ no ] = contador++;
	pilha[ sp++ ] = no;
	
	for( int i = last[ no ]; i != -1; i = pred[ i ] ){
		if( comp[ adj[i] ] != -1 ) continue;
		
		if( !marc[ adj[i] ] ){
			dfs( adj[i] );
			low[ no ] = min( low[ no ], low[ adj[i] ] );
		}else
			low[ no ] = min( low[no], tempo[ adj[i] ] );
	}
	
	if( tempo[ no ] == low[ no ] ){
		int temp;
		do{
			temp = pilha[ --sp ];
			comp[ temp ] = scc;
			++qtd[ scc ];
		}while( temp != no );
		++scc;
	}
	
}

set<int> dag[ N ];
vector<int> nos[ N ];
void tarjan(){
	contador = sp = scc = 0;
	memset( marc, false, sizeof( marc ) );
	memset( qtd, 0, sizeof( qtd ) );
	memset( comp, -1, sizeof( comp ) );
	for( int i = 0; i <= n; ++i ){
		if( !marc[ i ] )
			dfs( i );
	}
	
	for( int i = 0; i < scc; ++i ){
		dag[ i ].clear();
		nos[ i ].clear();
	}
	
	for( int i = 0; i < m; ++i ){
		if( comp[ adj[i] ] == comp[ ft[i] ] )
			nos[ comp[adj[i]] ].push_back( i );
		else
			dag[ comp[ ft[i] ] ].insert( comp[ adj[i] ] );  
	}
	
}


void busca( int no ){
	int sp = 1;
	pilha[ 0 ] = no;
	
	while( sp ){
		int at = pilha[ --sp ];
		
		for( set<int>::iterator it = dag[ at ].begin(); it != dag[ at ].end(); ++it ){
			if( !marc[ *it ] ){
				marc[ *it ] = true;
				pilha[ sp++ ] = *it;
			}
		}
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%d %d", &n, &m );
		memset( last, -1, sizeof( last ) );
		
		cont = 0;
		for( int i = 0; i < m; ++i ){
			int u, v, p;
			scanf( "%d %d %d", &v, &u, &p );
			add( u, v, p );
		}
	
		tarjan();
		memset( marc, false, sizeof( marc ) );
		for( int cp = 0; cp < scc; ++cp ){
			if( !nos[cp].size() ) continue;
			
			for( int i = 0; i <= n; ++i ) dist[ i ] = oo;
			dist[ ft[ nos[cp][0] ] ] = 0;
			for( int k = 0; k <= qtd[ cp ]; ++k ){
				for( int e = nos[ cp ].size() - 1; e >= 0; --e ){
					int ed = nos[ cp ][ e ];
					dist[ adj[ed] ] = min( dist[ adj[ed] ], dist[ ft[ed] ] + peso[ed] );
				}
			}
			
			if( dist[ ft[nos[cp][0]] ] < 0 )
				marc[ cp ] = true;
		}
		
		for( int i = 0; i < scc; ++i ){
			if( marc[ i ] )
				busca( i );
		}
		
		printf( "Case %d:", c );
		bool achou = false;
		for( int i = 0; i < n; ++i ){
			if( marc[ comp[i] ] ){
				printf( " %d", i );
				achou = true;
			}
		}
		
		if( achou )
			printf( "\n" );
		else
			printf( " impossible\n" );
	}
}


