#include <cstdio>
#include <cstring>

char linha[ 10000 ];
char mapa[] = "OIZEASGTBP";

int main(){
	int casos;
	scanf( "%d", &casos );
	gets( linha );
	
	for( int c = 1; c <= casos; ++c ){
		if( c != 1 )
			printf( "\n" );
		
		while( gets( linha ) && linha[ 0 ] ){
			for( int i = 0; linha[ i ]; ++i ){
				if( linha[ i ] >= '0' && linha[ i ] <= '9' )
					printf( "%c", mapa[ linha[ i ] - '0' ] );
				else
					printf( "%c", linha[ i ] );
			}
			printf( "\n" );
		}
	}
}

