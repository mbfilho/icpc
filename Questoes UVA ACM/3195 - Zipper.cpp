#include <cstdio>
#include <cstring>

char final[ 500 ], ini1[ 210 ], ini2[ 210 ];
int tam1, tam2;
int memo[ 201 ][ 201 ];

int possible( int i1 = 0, int i2 = 0 ){
	if( memo[ i1 ][ i2 ] != -1 )
		return memo[ i1 ][ i2 ];
		
	memo[ i1 ][ i2 ]  = 0;
	if( i1 < tam1 && ( ini1[ i1 ] == final[ i1 + i2 ] ) )
		memo[ i1 ][ i2 ] = possible( i1 + 1, i2 );
	if( i2 < tam2 && ( ini2[ i2 ] == final[ i1 + i2 ] ) )
		memo[ i1 ][ i2 ] = 	memo[ i1 ][ i2 ]  | possible( i1, i2 + 1 );
	
	return 	memo[ i1 ][ i2 ] ;
}

int main(){
	int casos;
	
	scanf( "%d", &casos );

	for( int i = 1; i <= casos; ++i ){
		scanf( "%s %s %s", ini1, ini2, final );
		
		tam1 = strlen( ini1 );
		tam2 = strlen( ini2 );
		for( int j = 0; j <= tam1; ++j ){
			for( int k = 0; k <= tam2; ++k )
				memo[ j ][ k ] = -1;
		}
		memo[ tam1 ][ tam2 ] = 1;
		
		if( possible() )
			printf( "Data set %d: yes\n", i );
		else
			printf( "Data set %d: no\n", i );
	
	}
}
