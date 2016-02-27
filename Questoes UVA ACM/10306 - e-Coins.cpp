#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define mp make_pair
#define oo 0x7fffffff
#define M 41

int n, m, s;
int valX[ M ], valY[ M ], pd[ 301 ][ 301 ];

int faz(){
	for( int j = 0; j <= s; ++j ){
		for( int k = 0; k <= s; ++k ){
			pd[ j ][ k ] = oo;
		}
	}

	pd[ 0 ][ 0 ] = 0;
	
	for( int x = 0; x <= s; ++x ){
		for( int y = 0; y <= s; ++y ){
			if( pd[ x ][ y ] == oo ) continue;
				
			for( int i = 0; i < m; ++i ){
				if( x + valX[i] <= s && y + valY[i] <= s )
					pd[ x + valX[ i ] ][ y + valY[ i ] ] = min( pd[ x + valX[ i ] ][ y + valY[ i ] ], pd[ x ][ y ] + 1 );
			}
		}
	}
	
	int menor = oo;
	for( int x = 0; x <= s; ++x ){
		for( int y = 0; y <= s; ++y ){
			if( ( x * x + y * y ) == s * s )
				menor = min( menor, pd[ x ][ y ] );
		}
	}
	
	
	return menor;
}

int main(){
	scanf( "%d", &n );
	while( n-- ){
		scanf( "%d %d", &m, &s );
		
		for( int i = 0; i < m; ++i )
			scanf( "%d %d", valX + i, valY + i );
		
		
		int qtd = faz();
		if( qtd == oo )
			printf( "not possible\n" );
		else
			printf( "%d\n", qtd );
	}
}

