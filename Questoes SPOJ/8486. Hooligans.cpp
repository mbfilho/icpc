#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int NO = 50 * 50;
const int EDGE = NO * NO;
const int TIMES = 50; 

int ultima[ NO ], atual[ NO ], nedges;
int seg[ EDGE ], res[ EDGE ], ant[ EDGE ];

void criar( int u, int v, int cap, bool t = true ){
	//u -> v
	ant[ nedges ] = ultima[ u ];	
	ultima[ u ] = nedges;
	
	seg[ nedges ] = v;
	res[ nedges ] = cap;
	++nedges;
	
	if( t )
		criar( v, u, 0, false );
}

int dist[ NO ], fila[ NO ];

bool bfs( int source, int sink ){
	memset( dist, -1, sizeof( dist ) );
	int ini = 0, fim = 1;

	dist[ source ] = 0;
	fila[ 0 ] = source;
	
	while( ini < fim ){
		int temp = fila[ ini++ ];
		
		for( int ar = ultima[ temp ]; ar != -1; ar = ant[ ar ] ){
			if( !res[ ar ] ) continue;
			
			if( dist[ seg[ar] ] == -1 ){
				dist[ seg[ar] ] = dist[ temp ] + 1;
				fila[ fim++ ] = seg[ar];
				if( seg[ar] == sink )
					return true;
			}
			
		}
	}	
	
	return false;
}

int dfs( int no, int sink, int minimo ){
	if( no == sink ) return minimo;
	
	for( int& ar = atual[ no ]; ar != -1; ar = ant[ ar ] ){
		if( !res[ ar ] || ( dist[ seg[ar] ] != dist[ no ] + 1 ) ) continue;
	//	printf( "Ar %d Val %d Nedge: %d obvio %d\n", ar, res[ ar ], nedges, min( minimo, res[ ar ] ) );
		int temp = dfs( seg[ ar ], sink, min( minimo, res[ ar ] ) );
		
		if( temp ){
			res[ ar ] -= temp;
			res[ ar xor 1 ] += temp;	
			return temp;
		}
	}
	
	return 0;
}

int dinic( int qtd, int source, int sink ){
	int fluxo = 0, val;
	
	while( bfs( source, sink ) ){
		for( int i = 0; i < qtd; ++i )
			atual[ i ] = ultima[ i ];
		atual[ source ] = ultima[ source ];
		atual[ sink ] = ultima[ sink ];
		
		while( val = dfs( source, sink, 100000 ) )
			fluxo += val;
	//	printf( "Voltei da dfs\n" );
	} 
	
	return fluxo;
}

int pts[ TIMES ], jogados[ TIMES ][ TIMES ];
int n, m, g;
 
int main(){
	while( scanf( "%d %d %d", &n, &m, &g ) && ( n | m | g ) ){
		memset( pts, 0, sizeof( pts ) );
		memset( jogados, 0, sizeof( jogados ) );
		
		int restantes = m * n * ( n - 1 ) / 2;
		for( int i = 0; i < g; ++i ){
			int a, b;
			char op[ 10 ];
			scanf( "%d %s %d", &a, op, &b );
			++jogados[ a ][ b ];
			++jogados[ b ][ a ];
			--restantes;
			switch( op[ 0 ] ){
				case '=':
					++pts[ a ];
					++pts[ b ];
					break;
				case '<':
					pts[ b ] += 2;
					break;
				case '>':
					pts[ a ] += 2;
					break;
			}
		}

	//	printf( "Jogadores\n" );
		for( int i = 1; i < n; ++i ){
			pts[ 0 ] += ( m - jogados[ 0 ][ i ] ) * 2;
			restantes -= (  m - jogados[ 0 ][ i ] );
			jogados[ 0 ][ i ] = jogados[ i ][ 0 ] = m;
		}
		
		nedges = 0;
		memset( ultima, -1, sizeof( ultima ) );
		
		int source = n + restantes;
		int sink = source + 1;
		int cont = 0;	
		bool dm = false;
		for( int i = 1; i < n; ++i ){
			if( pts[ 0 ] <= pts[ i ] ){
				dm = true;
				break;
			}
			
			criar( i, sink, pts[ 0 ] - 1 - pts[ i ] );
			for( int j = i + 1; j < n; ++j ){
				if( m - jogados[ i ][ j ] ){
					criar( n + cont, i, ( m - jogados[ i ][ j ] ) * 2 );
					criar( n + cont, j, ( m - jogados[ i ][ j ] ) * 2 );
					criar( source, n + cont, ( m - jogados[ i ][ j ] ) * 2 );
					++cont;
				}
			}
		}
		
		//printf( "Criei, vou para o fluxo!\n" );
		if( !dm && dinic( n + cont, source, sink ) == 2 * restantes )
			printf( "Y\n" );
		else
			printf( "N\n" ); 
	}
}



