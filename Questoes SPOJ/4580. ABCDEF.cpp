#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define N 110

int num[ N ];
int s1[ N * N * N ], s2[ N * N * N ];
int n;

int first( int* ar, int tam, int val ){
	int ini = 0, fim = tam - 1, meio, best = -1;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ar[ meio ] >= val ){
			fim = meio - 1;
			if( ar[ meio ] == val )
				best = meio;
		}else
			ini = meio + 1;
	}
	
	return best;
}

int last( int* ar, int tam, int val ){
	int ini = 0, fim = tam - 1, meio, best = -2;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ar[ meio ] <= val ){
			ini = meio + 1;
			if( ar[ meio ] == val )
				best = meio;
		}else
			fim = meio - 1;
	}
	
	return best;
}

int main(){
	
	while( scanf( "%d", &n ) != EOF ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", num + i );
		
		int c1 = 0, c2 = 0;
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j ){
				for( int k = 0; k < n; ++k ){
					s1[ c1++ ] = num[ i ] * num[ j ] + num[ k ];
					if( num[ k ] )
						s2[ c2++ ] = num[ k ] * ( num[ i ] + num[ j ] );
				}
			}
		}
		
		sort( s2, s2 + c2 );
		sort( s1, s1 + c1 );
		ll soma = 0;
		for( int i = 0; i < c1; ){
			int tam = last( s1, c1, s1[ i ] ) - i + 1;
			 
			soma += ( last( s2, c2, s1[ i ] ) - first( s2, c2, s1[ i ] ) + 1 ) * tam;
			i += tam;
		}
		printf( "%lld\n", soma );
		
	}
}

