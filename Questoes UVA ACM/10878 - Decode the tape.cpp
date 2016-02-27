#include <cstdio>
#include <cstring>

char array[ 50000 ];

int main(){
	char parada[] = "___________";
	char impressao[ 50000 ];
	int imp = 0;
	
	gets( array );
	
	char code;
	int cont;
	int pot;
	int tam;
	while( gets( array ) && strcmp( array, parada ) != 0 ){
		pot = 1 << 7;
		cont = 0;
		code = 0;
		tam = strlen( array );
		
		for( int i = 0; i < tam; ++i ){
			if( array[ i ] == ' ' ){
				pot = pot >> 1;
				++cont;
			}else if( array[ i ] == 'o' ){
				code = code | pot;
				pot = pot >> 1;
				++cont;
			}
		}

		if( cont == 8 )
			impressao[ imp++ ] = code;		
	}
	
	if( imp )
		printf( "%s", impressao );
	

}
