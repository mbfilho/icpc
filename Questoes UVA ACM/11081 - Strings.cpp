#include <cstring>
#include <cstdio>
#define mod 10007
char a1[ 80 ], a2[ 80 ], a3[ 80 ];

int t1, t2, t3;
int memo[ 80 ][ 80 ][ 80 ];

int rec( int a, int b, int c ){
	if( memo[ a ][ b ][ c ] != - 1 )
		return memo[ a ][ b ][ c ];
		
	int &retorno = memo[ a ][ b ][ c ];
	
	if( c == t3 )
		return retorno = 1;
	if( a == t1 && b == t2 )
		return retorno = 0;

	retorno = 0;
	for( int i = a; i < t1; ++i ){
		if( a1[ i ] == a3[ c ] )
			retorno = ( retorno + rec( i + 1, b, c + 1 ) ) % mod;
	}
	
	for( int i = b; i < t2; ++i ){
		if( a2[ i ] == a3[ c ] )
			retorno = ( retorno + rec( a, i + 1, c + 1 ) ) % mod;
	}
	
	return retorno;
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%s %s %s", a1, a2, a3 );
			
		t1 = strlen( a1 );
		t2 = strlen( a2 );
		t3 = strlen( a3 );
		for( int i = 0; i <= t1; ++i ){
			for( int j = 0; j <= t2; ++j ){
				for( int k = 0; k <= t3; ++k )
					memo[ i ][ j ][ k ] = -1;
			}
		}
		printf( "%d\n", rec( 0, 0, 0 ) );
	}
}
