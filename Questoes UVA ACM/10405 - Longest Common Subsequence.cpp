#include <cstdio>
#include <cstring>
#define max( a, b ) (a) > (b)? (a) : (b)

char s1[ 1001 ], s2[ 1001 ];
int tam1, tam2;
int pd[ 1001 ][ 1001 ];

int lcs(){
	for( int i = 1; i <= tam1; ++i ){
		for( int j = 1; j <= tam2; ++j ){
			if( s1[ i - 1 ] == s2[ j - 1 ] )
				pd[ i ][ j ] = pd[ i - 1 ][ j - 1 ] + 1;
			else
				pd[ i ][ j ] = max( pd[ i - 1 ][ j ], pd[ i ][ j - 1 ] );
		}
	}
	
	return pd[ tam1 ][ tam2 ];
}

int main(){
	for( int i = 0; i < 1001; ++i )
		pd[ i ][ 0 ] = pd[ 0 ][ 1 ] = 0;
	
	while( gets( s1 ) ){
		gets( s2 );
		tam1 = strlen( s1 );
		tam2 = strlen( s2 );
		printf( "%d\n", lcs() );
	}
}
