#include <cstdio>
#include <cstring>

int main(){
	char linha[ 2000 ];
	
	while( gets( linha ) && linha[ 0 ] != '#' ){
		for( int i = 0; linha[ i ]; ++i ){
			switch( linha[ i ] ){
				case ' ':
					printf( "%%20" );
					break;
				case '!':
					printf( "%%21" );
					break;
				case '$':
					printf( "%%24" );
					break;
				case '%':
					printf( "%%25" );
					break;
				case '(':
					printf( "%%28" );
					break;
				case ')':
					printf( "%%29" );
					break;
				case '*':
					printf( "%%2a" );
					break;
				default:
					printf( "%c", linha[ i ] );
			}
		}
		printf( "\n" );
	}
}

