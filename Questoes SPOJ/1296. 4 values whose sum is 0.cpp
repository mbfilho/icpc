#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 4100

int a[ N ], b[ N ], c[ N ], d[ N ];
int s1[ N * N ], s2[ N * N ];
int n;

int first( int* ar, int tam, int val ){
	int ini = 0, fim = tam - 1, meio, best = -1;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ar[ meio ] == val ){
			best = meio;
			fim = meio - 1;
		}else if( ar[ meio ] > val )
			fim = meio - 1;
		else
			ini = meio + 1;
	}
	
	return best;
}

int last( int* ar, int tam, int val ){
	int ini = 0, fim =  tam - 1, meio, best = -2;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ar[ meio ] == val ){
			best = meio;
			ini = meio + 1;
		}else if( ar[ meio ] > val )
			fim = meio - 1;
		else
			ini = meio + 1;
	}
	
	return best;
}

int main(){
	
	while( scanf( "%d", &n ) != EOF ){
		for( int i = 0; i < n; ++i )
			scanf( "%d %d %d %d", a + i, b + i, c + i, d + i );
		
		int cont = 0;
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j ){
				s1[ cont ] = a[ i ] + b[ j ];
				s2[ cont++ ] = c[ i ] + d[ j ];
			}
		}
		
		sort( s1, s1 + cont );
		sort( s2, s2 + cont );
		ll soma = 0;
		
		for( int i = 0; i < cont; ){
			int tam = last( s1, cont, s1[ i ] ) - i + 1;
			soma += ( last( s2, cont, -s1[ i ] ) - first( s2, cont, -s1[ i ] ) + 1 ) * tam;
			i += tam;
		}
		printf( "%lld\n", soma );
	}
}







