#include <cstdio>
#include <cstdlib>

int ori[ 1000 ][ 1000 ], vetor[ 1000 ], temp2[ 1000 ], temp[ 1000 ], comp[ 1000 ][ 1000 ];
int n;

void multi( int ma[ 1000 ][ 1000 ], int *vec, int* dest ){
	for( int i = 0; i < n; ++i ){
		dest[ i ] = 0;
		for( int j = 0; j < n; ++j )
			dest[ i ] += ma[ i ][ j ] * vec[ j ];
	}
}

int main(){
	for( int i = 0; i < 1000; ++i ) 
		vetor[ i ] = rand();
		
	while( scanf( "%d", &n ) && n ){
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j )
				scanf( "%d", &ori[ i ][ j ] );
		}
		
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j )
				scanf( "%d", &comp[ i ][ j ] );
		}
		
		bool dm = false;
		for( int c = 0; c < 1 && dm == false; ++c ){		
			//temp = ori * vetor
			multi( ori, vetor, temp );
			
			//temp2 = ori * ori * vetor
			multi( ori, temp, temp2 );
			
			//temp = comp * vetor
			multi( comp, vetor, temp );

			for( int i = 0; i < n; ++i ){
				if( temp[ i ] != temp2[ i ] ){
					dm = true;
					break;
				}
			}
			
			for( int i = 0; i < n; ++i )
				vetor[ i ] = temp[ i ] | temp2[ i ];
		}
		
		if( dm )
			printf( "NO\n" );
		else
			printf( "YES\n" );
	}
	
}
