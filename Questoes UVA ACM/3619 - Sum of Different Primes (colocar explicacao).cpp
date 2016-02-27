#include <cstdio>
#include <algorithm>
using namespace std;

bool crivo[ 1121 ];
int primos[ 200 ], contp;
int memo[ 1121 ][ 188 ][ 15 ];

void gerar(){
	fill( crivo, crivo + 1121, true );
	
	for( int i = 4; i < 1121; i += 2 )
		crivo[ i ] = false;
	
	for( int i = 3; i * i < 1121; i += 2 ){
		if( !crivo[ i ] ) continue;
		
		for( int j = i * i; j < 1121; j += 2 * i )
			crivo[ j ] = false;
	}
	
	primos[ 1 ] = 2;
	contp = 2;
	for( int i = 3; i < 1121; i += 2 ){
		if( crivo[ i ] )
			primos[ contp++ ] = i;
	}
	
//	printf( "%d\n", contp );
}

int rec( int n, int i, int k ){
	int &retorno = memo[ n ][ i ][ k ];
	
	if( retorno != -1 ) return retorno;
	
	if( i == 0 ) return retorno = 0;
	if( k == 0 ) return retorno = 0;
	
	if( n == primos[ i ] && k == 1 )
		return retorno = 1;
		
	retorno = rec( n, i - 1, k );
	
	if( n - primos[ i ] >= 0 ){
//		printf( "AQui: %d %d %d\n", n, primos[i], i );
		retorno += rec( n - primos[ i ], i - 1, k - 1 );
	}
	
	return retorno;
}

int main(){
	gerar();
	for( int i = 0; i < 1121; ++i ){
		for( int p = 0; p < 188; ++p ){
			for( int k = 0; k < 15; ++k )
				memo[ i ][ p ][ k ] = -1;
		}
	}
	
	int n, k;
	while( scanf( "%d %d", &n, &k ) && ( n | k ) ){
		printf( "%d\n", rec( n, 187, k ) );
	}
}
