#include <cstdio>
#include <cstring>
#define max( a, b ) (a) > (b)? (a) : (b)

/*
* É só aplicar o Long Commom Subsequence para a string original e a string invertida!
*/

char s1[ 1100 ];
char inver[ 1100 ];
int tam;

int pd[ 1100 ][ 1100 ];

int lcs(){
	for( int i = 0; i < tam; ++i )
		inver[ i ] = s1[ tam - 1 - i ];

	for( int i = 1; i <= tam; ++i ){
		for( int j = 1; j <= tam; ++j ){
			if( s1[ i - 1 ] == inver[ j - 1 ] ){
				pd[ i ][ j ] = 1 + pd[ i - 1 ][ j - 1 ]; 
			}else
				pd[ i ][ j ] = max( pd[ i - 1 ][ j ], pd[ i ][ j - 1 ] );
		}
	}
		
	return pd[ tam ][ tam ];
}

int main(){
	int t;
	scanf( "%d", &t );
	getc( stdin );
	
	for( int i = 0; i < 1100; ++i )
		pd[ i ][ 0 ] = pd[ 0 ][ i ] = 0;
		
	while( t-- ){
		gets( s1 );
		tam = strlen( s1 );
		if( tam > 0 )
			printf( "%d\n", lcs() );
		else
			printf( "0\n" );
	}
}


