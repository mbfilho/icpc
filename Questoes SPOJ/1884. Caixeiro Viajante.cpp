#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define mp make_pair
#define N 110
int c, s, e, t;
int fim[ N ];
int dist[ N ][ N ];
int lucro[ N ][ N ], aux[ N ][ N ];
//http://br.spoj.pl/problems/CAIXVIAJ/
//http://br.spoj.pl/problems/SEQUE/

void mult( int a[ N ][ N ], int b[ N ][ N ], int resp[ N ][ N ] ){
	int temp[ c ][ c ];
	for( int i = 0; i < c; ++i ){
		for( int j = 0; j < c; ++j )
			temp[ i ][ j ] = a[ i ][ j ];
	}	
	
	for( int k = 0; k < c; ++k ){
		for( int i = 0; i < c; ++i ){
			for( int j = 0; j < c; ++j )
				temp[ i ][ j ] = max( temp[ i ][ j ], a[ i ][ k ] + b[ k ][ j ] );
		}
	}
	
	for( int i = 0; i < c; ++i ){
		for( int j = 0; j < c; ++j )
			resp[ i ][ j ] = temp[ i ][ j ];
	}
}

void expo( int xp ){
	bool first = true;
	
	int it = 1;
		
	while( xp ){
		if( xp & 1 ){
			if( !first )
				mult( aux, lucro, aux );
			else{
				first = false;
				for( int i = 0; i < c; ++i ){
					for( int j = 0; j < c; ++j )
						aux[ i ][ j ] = lucro[ i ][ j ];
				}
			}
		}
		mult( lucro, lucro, lucro );

		xp = xp >> 1;
	}
	
	for( int i = 0; i < c; ++i ){
		for( int j = 0; j < c; ++j )
			lucro[ i ][ j ] = aux[ i ][ j ];
	}
}

int faz(){
	for( int i = 0; i < c; ++i ){
		for( int j = 0; j < c; ++j ){
			if( i == s )
				dist[ i ][ j ] = lucro[ i ][ j ];
			else
				dist[ i ][ j ] = 0;
		}
	}
	
	if( t - 1 ){
		expo( t - 1 );
		mult( dist, lucro, dist );
	}
	
	int maior = -1;
	for( int i = 0; i < e; ++i ){
		for( int j = 0; j < c; ++j ){
			maior = max( maior, dist[ j ][ fim[i] ] );
		}
	}
	
	return maior;
}

int main(){
	while( scanf( "%d %d %d %d", &c, &s, &e, &t ) && ( c | s | e | t ) ){
		--s;
		
		for( int i = 0; i < c; ++i ){
			for( int j = 0; j < c; ++j )
				scanf( "%d", &lucro[ i ][ j ] );
		}

		for( int i = 0; i < e; ++i ){
			scanf( "%d", fim + i );
			--fim[ i ];
		}
		
		int resp = faz();
		printf( "%d\n", resp );
	}
}




