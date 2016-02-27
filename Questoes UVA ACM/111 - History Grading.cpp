#include <cstdio>
#define max( a, b ) (a) > (b)? (a) : (b);

int pd[ 21 ][ 21 ];
int correta[ 21 ], estudante[ 21 ];
int n;

int lcs(){
	for( int i = 1; i <= n; ++i ){
		for( int j = 1; j <= n; ++j ){
			if( estudante[ i ] == correta[ j ] )
				pd[ i ][ j ] = pd[ i - 1 ][ j - 1 ] + 1;
			else
				pd[ i ][ j ] = max( pd[ i - 1 ][ j ], pd[ i ][ j - 1 ] );
		}
	}
	
	return pd[ n ][ n ];
}

int main(){
	int temp;
	
	for( int i = 0; i < 21; ++i )
		pd[ 0 ][ i ] = pd[ i ][ 0 ] = 0;
		
	scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ){
		scanf( "%d", &temp );
		correta[ temp ] = i;
	}
	
	
	while( scanf( "%d", &temp ) != EOF ){
		estudante[ temp ] = 1;
		
		for( int i = 2; i <= n; ++i ){
			scanf( "%d", &temp );
			estudante[ temp ] = i;
		}
		printf( "%d\n", lcs() );
	}
	
}
