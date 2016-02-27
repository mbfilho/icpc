#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

double dist[ 21 ][ 21 ][ 21 ];
int parent[ 21 ][ 21 ][ 21 ];
int n;

void print( int i, int j, int k ){
	if( k == 0 )
		printf( "%d", parent[ i ][ j ][ k ] );
	else{
		print( i, parent[ i ][ j ][ k ], k - 1 );
		printf( " %d", parent[ i ][ j ][ k ] );
	}
}

int main(){
	while( scanf( "%d", &n ) != EOF ){
		for( int i = 1; i <= n; ++i ){
			for( int j = 1; j <= n; ++j ){
				parent[ i ][ j ][ 0 ] = i;
				
				if( i == j )
					dist[ i ][ i ][ 0 ] = 0.0;
				else{
					scanf( "%lf", &dist[ i ][ j ][ 0 ] );
					dist[ i ][ j ][ 0 ] = - log10( dist[ i ][ j ][ 0 ] );
				}
			}		
		}
				
		for( int s = 0; s < n; ++s ){
			for( int i = 1; i <= n; ++i ){
				for( int j = 1; j <= n; ++j ){
					dist[ i ][ j ][ s + 1 ] = 9999999;

					for( int k = 1; k <= n; ++k ){
						if( dist[ i ][ j ][ s + 1 ] > dist[ i ][ k ][ s ] + dist[ k ][ j ][ 0 ] ){
							dist[ i ][ j ][ s + 1 ] = dist[ i ][ k ][ s ] + dist[ k ][ j ][ 0 ];
							parent[ i ][ j ][ s + 1 ] = parent[ k ][ j ][ s ];
						}
					}
				}
			}
		}
	
		bool caminho = false;
		for( int k = 1; k <= n && !caminho; ++k ){
			for( int i = 1; i <= n; ++i ){
				//printf( "%lf\n", dist[ i ][ i ][ k ] );
				if( dist[ i ][ i ][ k ] <= -log10( 1.01 ) ){
					
					print( i, i, k );
					printf( " %d\n", i );
					caminho = true;
					break;
				}
			}
		}
	
		if( caminho == false )
			printf( "no arbitrage sequence exists\n" );			
	}
}
