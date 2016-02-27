#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 10100

int subC[ N ], subD[ N ];
int temp[ N ];
int seq[ N ], rev[ N ], n;

int bs( int* ar, int tam, int val ){
	int ini = 1, fim = tam, meio, ret = 0;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ar[ temp[meio] ] >= val )
			fim = meio - 1;
		else{
			ret = meio;
			ini = meio + 1;
		} 
	}
	
	return ret;
}

void crescente( int* ar, int* result ){
	int tam = 1;
	temp[ 1 ] = 0;
	result[ 0 ] = 1;
	
	for( int i = 1; i < n; ++i ){
		int res = bs( ar, tam, ar[ i ] );		
		result[ i ] = res + 1;		
		if( res == tam || ar[ temp[res + 1] ] > ar[ i ] ){
			temp[ res + 1 ] = i;
			tam = max( tam, res + 1 );
		}
	}
}

int main(){
	while( scanf( "%d", &n ) != EOF ){
		for( int i = 0; i < n; ++i ){
			scanf( "%d", seq + i );
			rev[ n - 1 - i ] = seq[ i ];
		}
		
		crescente( seq, subC );
		crescente( rev, subD );

		int wavio = -1;
		for( int i = 0; i < n; ++i ){
			int tam =  min( subC[ i ] - 1, subD[ n - 1 - i ] - 1 );
			wavio = max( wavio, tam * 2 + 1 );
		}
		
		printf( "%d\n", wavio );
	}
}




