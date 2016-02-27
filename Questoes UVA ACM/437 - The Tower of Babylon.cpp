#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 110

int pts[ N ][ 3 ], n;
int pd[ N ][ 6 ];

int faz( int* atual, int ind, int per ){
	if( pd[ ind ][ per ] != -1 ) return pd[ ind ][ per ];
	int maior = atual[ 2 ];
	
	for( int i = 0; i < n; ++i ){
		int temp[ 3 ];
		for( int h = 0; h < 3; ++h )
			temp[ h ] = pts[ i ][ h ];
		sort( temp, temp + 3 );
		
		int cont = 0;
		do{
			if( temp[ 0 ] < atual[ 0 ] && temp[ 1 ] < atual[ 1 ] ){
				maior = max( maior, atual[ 2 ] + faz( temp, i, cont ) );
			}
			++cont;
		}while( next_permutation( temp, temp + 3 ) );
	}
	
	return pd[ ind ][ per ] = maior;
}

int main(){
	int caso = 1;
	
	while( scanf( "%d", &n ) && n ){
		for( int i = 0; i < n; ++i )
			scanf( "%d %d %d", pts[ i ], pts[ i ] + 1, pts[ i ] + 2 );
		
		int maior = -1;
		
		memset( pd, -1, sizeof( pd ) );
		for( int i = 0; i < n; ++i ){
			sort( pts[ i ], pts[ i ] + 3 );
			int cont = 0;
			do{
				maior = max( maior, faz( pts[ i ], i, cont ) );
				++cont;
			}while( next_permutation( pts[ i ], pts[ i ] + 3 ) );
		}
		printf( "Case %d: maximum height = %d\n", caso++, maior );
	}
}

