#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int ma[ 2000 ][ 2000 ];
int tam, t2;
char nome[ 5000 ], n2[ 5000 ];

int main(){

	while( scanf( "%s %s", nome, n2 ) != EOF ){
		tam = strlen( nome );
		t2 = strlen( n2 );
		
		for( int i = 0; i <= tam; ++i )
			ma[ 0 ][ i ] = 0;
		for( int i = 0; i <= t2; ++i )
			ma[ i ][ 0 ] = 0;
	
		for( int i = 1; i <= tam; ++i ){
			for( int j = 1; j <= t2; ++j ){
				if( nome[ i - 1 ] == n2[ j - 1 ] )
					ma[ i ][ j ] = ma[ i - 1 ][ j - 1 ] + 1;
				else
					ma[ i ][ j ] = max( ma[ i - 1 ][ j ], ma[ i ][ j - 1 ] );
			}
		}
	
		printf( "%d\n", ma[ tam ][ t2 ] );
	}
}

