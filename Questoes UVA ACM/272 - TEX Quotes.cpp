#include <cstdio>

int main(){
	int c;
	bool first = true;
	
	while( ( c = getc( stdin ) ) != EOF ){
		if( c == '"' ){
			if( first ){
				first = false;
				printf( "``" );
			}else{
				first = true;
				printf( "''" );
			}
		}else
			printf( "%c", char( c ) );
	}
}
