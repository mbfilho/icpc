#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int soma[ 30 ][ 30 ], temp[ 30 ][ 30 ], cid[ 30 ][ 30 ];

void mult( int a[30][30], int b[30][30], int c[30][30] ){
	int var, auxi[ n ][ n ];
	
	for( int i = 0; i < n; ++i ){
		for( int j = 0; j < n; ++j ){
			var = 0;
			for( int k = 0; k < n; ++k ){
				var += ( b[ i ][ k ] * c[ k ][ j ] );
				auxi[ i ][ j ] = var;
			}
		}
	}
	
	for( int i = 0; i < n; ++i ){
		for( int j = 0; j < n; ++j )
			a[ i ][ j ] = auxi[ i ][ j ];
	}
}

int main(){
	int ruas, a, b, casos = 0;
	
	while( scanf( "%d", &ruas ) != EOF ){
		printf( "matrix for city %d\n", casos );
		++casos;
		n = -1;
		
		for( int i = 0; i < 30; ++i ){
			for( int j = 0; j < 30; ++j )
				soma[ i ][ j ] = temp[ i ][ j ] = cid[ i ][ j ] = 0;			
			temp[ i ][ i ] = 1;
		}
		
		while( ruas-- ){
			scanf( "%d %d", &a, &b );
			if( a > n )
				n = a;
			if( b > n )
				n = b;
			cid[ a ][ b ] = 1;
		}
		
		++n;
		for( int i = 0; i < n - 1; ++i ){
			mult( temp, cid, temp );
			
			for( int j = 0; j < n; ++j ){
				for( int k = 0; k < n; ++k )
					soma[ j ][ k ] += temp[ j ][ k ];
			}
		}
		
		bool tdZero;
		for( int i = 0; i < n; ++i ){
			mult( temp, cid, temp );
			
			tdZero = true;
			for( int j = 0; j < n; ++j ){
				for( int k = 0; k < n; ++k ){
					if( temp[ j ][ k ] != 0 ){
						soma[ j ][ k ] = -1;
						tdZero = false;
					}
				}	
			}		
			if( tdZero )
				break;
		}
		
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j )
				printf( "%d%c", soma[ i ][ j ], ( j == n - 1 ) ? '\n' : ' ' );
		}
		
	}
}

