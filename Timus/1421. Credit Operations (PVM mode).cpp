#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

#define MAX_NO 220
const int MAX_EDG = 2 * ( 100 * 100 + 200 );

int last[ MAX_NO ], ante[ MAX_EDG ], atual[ MAX_NO ], res[ MAX_EDG ], adj[ MAX_EDG ];
int dist[ MAX_NO ];
int nedge, n;
int fila[ 2 * MAX_EDG ];
int source, sink;

void add( int a, int b, int cap ){
	ante[ nedge ] = last[ a ];
	last[ a ] = nedge;
	adj[ nedge ] = b;
	res[ nedge ] = cap;
	++nedge;
}

bool bfs(){
	int ini = 0, fim = 1, temp, next;
	memset( dist, -1, sizeof( dist ) );
	fila[ 0 ] = source;
	dist[ source ] = 0;
	
	for( int i = 0; i < 2 * n + 2; ++i )
		atual[ i ] = last[ i ];
		
	while( ini < fim ){
		temp = fila[ ini++ ];
		
		for( int i = last[ temp ]; i != -1; i = ante[ i ] ){
			next = adj[ i ];
			if( dist[ next ] == -1 && res[ i ] ){
				dist[ next ] = dist[ temp ] + 1;
				if( next == sink ) return true;
				fila[ fim++ ] = next;
			}
		}
	}
	
	return false;
}

int rev( int arg ){
	return arg ^ 1;
}

int dfs( int no, int acc ){
	if( no == sink ) return acc;
	
	int val;
	for( int& i = atual[ no ]; i != -1; i = ante[ i ] ){
//		printf( "(%d,%d) %d == %d %d\n", no, adj[i], dist[ adj[i] ], res[ i ] );
		if( dist[ no ] + 1 == dist[ adj[i] ] && res[ i ] ){
			val = dfs( adj[ i ], min( acc, res[ i ] ) );
			if( val ){
				res[ i ] -= val;
				res[ rev( i ) ] += val;
				return val;
			}
		}
	}
	
	return 0;
}

 
int main(){
	int dado[ 101 ], rece[ 101 ];
	
	while( scanf( "%d", &n ) != EOF ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", rece + i );
		for( int i = 0; i < n; ++i )
			scanf( "%d", dado + i );
		nedge = 0;

		memset( last, -1, sizeof( last ) );
		source = 2 * n;
		sink = source + 1;
		
		for( int i = 0; i < n; ++i ){
			add( source, i, rece[ i ] );
			add( i, source, 0 );
		} 
		
		for( int i = n; i < 2 * n; ++i ){
			add( i, sink, dado[ i - n ] );
			add( sink, i, 0 );
		}
		
		for( int i = 0; i < n; ++i ){
			for( int j = 2 * n - 1; j >= n; --j ){
				add( i, j, 100 );
				add( j, i, 0 );
			}
		}
		
		int maxFlow = 0;
		while( bfs() ){
			int flow = 0;

			while( flow = dfs( source, 10000000 ) ){
//				printf( "Flow %d MaxFlow %d\n", flow, maxFlow );
				maxFlow += flow;
			}
		}
		
		int soma = 0;
		for( int i = 0; i < n; ++i )
			soma += rece[ i ];
				
		if( soma != maxFlow )
			printf( "NO\n" );
		else{
			printf( "YES\n" );
			for( int i = 0; i < n; ++i ){
				printf( "%d", 100 - res[ last[i] ] );
				
				for( int j = ante[ last[ i ] ]; adj[ j ] != source; j = ante[ j ] )
					printf( " %d", 100 - res[ j ] );
				printf( "\n" );
			}
		}
	}
}




