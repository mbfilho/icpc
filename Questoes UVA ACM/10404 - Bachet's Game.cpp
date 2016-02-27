#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000020

int n, m, conj[ 11 ];

bool pd[ N ][ 2 ]; 

int main(){
	while( scanf( "%d %d", &n, &m ) != EOF ){
		for( int i = 0; i < m; ++i ){
			scanf( "%d", conj + i );
			//printf( "A %d\n", conj[ i ] );
		}
		
		sort( conj, conj + m );
		for( int i = 0; i <= n; ++i )
			pd[ i ][ 0 ] = pd[ i ][ 1 ] = false;
		
		for( int i = 0; i <= n; ++i ){
			for( int j = 0; j < m; ++j ){
				if( i + conj[ j ] > n ) break;
				pd[ i + conj[ j ] ][ 0 ] |= !pd[ i ][ 1 ];
				pd[ i + conj[ j ] ][ 1 ] |= !pd[ i ][ 0 ];
			}
		}
		
		if( pd[ n ][ 0 ] )
			printf( "Stan wins\n" );
		else
			printf( "Ollie wins\n" );
	}
}

