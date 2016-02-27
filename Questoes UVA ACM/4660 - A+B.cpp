#include <cstdio>

int main(){
	char a[ 10 ], b[ 10 ];
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%s %s", a, b );
		
		int mA = -1, mB = -1;
		for( int i = 0; a[ i ] != '\0'; ++i ){
			if( a[ i ] - '0' > mA )
				mA = a[ i ] - '0';
		}
		for( int i = 0; b[ i ] != '\0'; ++i ){
			if( b[ i ] - '0' > mB )
				mB = b[ i ] - '0';
		}
		
		++mA;
		++mB;
		int vala = 0, valb = 0;
		for( int i = 0; a[ i ] != '\0'; ++i ){
			vala = vala * mA + ( a[ i ] - '0' );
		}
		
		for( int i = 0; b[ i ] != '\0'; ++i ){
			valb = valb * mB + ( b[ i ] - '0' );
		}
		
		printf( "%d\n", vala + valb );
	}
	
}

