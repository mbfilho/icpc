#include <cstdio>
#include <algorithm>
using namespace std;
#define inf 0x99999

int dist[ 21 ][ 21 ];

int main(){
	int qtd, temp, querys, a, b, cont = 1;
	
	while( scanf( "%d", &qtd ) != EOF ){
		printf( "Test Set #%d\n", cont );
		++cont;
		
		for( int i = 1; i <= 20; ++i ){
			for( int j = 1; j <= 20; ++j )
				dist[ i ][ j ] = inf;
			dist[ i ][ i ] = 0;
		}
		
		for( int i = 0; i < qtd; ++i ){
			scanf( "%d", &temp );
			dist[ 1 ][ temp ] = dist[ temp ][ 1 ] = 1;
		}
		
		for( int i = 2; i < 20; ++i ){
			scanf( "%d", &qtd );
			for( int j = 0; j < qtd; ++j ){
				scanf( "%d", &temp );
				dist[ i ][ temp ] = dist[ temp ][ i ] = 1;
			}
		}
		
		//Floyd-Warshall
		for( int k = 1; k <= 20; ++k ){
			for( int i = 1; i <= 20; ++i ){					
				for( int j = 1; j <= 20; ++j ){					
					dist[ i ][ j ] = min( dist[ i ][ j ], dist[ i ][ k ] + dist[ k ][ j ] );
					dist[ j ][ i ] = dist[ i ][ j ];
				}
			}
		}
		
		scanf( "%d", &querys );
		for( int q = 0; q < querys; ++q ){
			scanf( "%d %d", &a, &b );
			printf( "%2d to %2d: %-d\n", a, b, dist[ a ][ b ] );
		}
		printf( "\n" );
	}
	
}
