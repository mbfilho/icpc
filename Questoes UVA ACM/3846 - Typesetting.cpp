#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


char painel[ 22 ][ 500 ];
char tp[ 22 ][ 30 ][ 30 ];
int parede = 25, alt, n;
int prox[ 22 ];

int dist( int glifo, int linha ){
	int qtd = 0;
	
	while( tp[ glifo ][ linha ][ qtd ] && tp[ glifo ][ linha ][ qtd ] == '.' ){
		++qtd;
	}
	
	if( qtd == strlen( tp[ glifo ][ linha ] ) )
		return -1;
		
	return prox[ linha ] - qtd;
}

int incr( int glifo, int linha, int frente ){
	int tam = strlen( tp[ glifo ][ linha ] );
	int qtd = tam - 1;
	
	while( qtd >= 0 && tp[ glifo ][ linha ][ qtd ] == '.' ){
		--qtd;
	}
	
	++qtd; //qtd de caracteres!	
	if( qtd )
		prox[ linha ] = max( prox[ linha ], frente + qtd + 1 );		
}

int main(){
	char linha[ 1000 ];
	int caso = 1;
	
	while( scanf( "%d", &alt ) && alt ){
		printf( "%d\n", caso++ );
		
		for( int i = 0; i < 22; ++i ){
			for( int j = 0; j < 500; ++j )
				painel[ i ][ j ] = '.';
		}
		for( int i = 0; i < 22; ++i ) prox[ i ] = 0;
		
		gets( linha );
		
		for( int i = 0; i < alt; ++i ){
			n = 0;
			gets( linha );
			int temp = 0, aux;
			
			while( sscanf( linha + temp, "%s %n", tp[ n ][ i ], &aux ) != EOF ){
				temp += aux;
				++n;
			}
		}
		for( int i = 0; i < alt; ++i ){
			for( int j = strlen( tp[ 0 ][ i ] ) - 1; j >= 0; --j )
				painel[ i ][ j + parede ] = tp[ 0 ][ i ][ j ];
			incr( 0, i, parede );
		//	printf( "Prox %d\n", prox[i] );
		}
		
		int menor;
		for( int i = 1; i < n; ++i ){
			menor = 0;
			for( int j = 0; j < alt; ++j ){
			//	printf( "Na linha %d: %d\n", j, dist( i, j ) );
				menor = max( menor, dist( i, j ) );
			}
			
					
		//	printf( "AQUI %d\n", menor );
			for( int k = 0; k < alt; ++k ){
		//		printf( ">>> %s\n", tp[ i ][ k] );
				for( int col = strlen( tp[ i ][ k ] ) - 1; col >= 0; --col ){
					if( tp[ i ][ k ][ col ] != '.' ){
		//				printf( "%d\n", col + menor );
						painel[ k ][ col + menor ] = tp[ i ][ k ][ col ];
					}
				}
			}
			for( int j = 0; j < alt; ++j )
				incr( i, j, menor );
		}
		
		int menorGeral = -1, maiorGeral = -1;
		for( int j = 0; menorGeral == -1 && j < 500; ++j ){
			for( int i = 0; i < alt; ++i ){
				if( painel[ i ][ j ] == '#' ){
					menorGeral = j;
					break;
				}
			}
		}		
		
		for( int j = 499; maiorGeral == -1 && j >= 0; --j ){
			for( int i = 0; i < alt; ++i ){
				if( painel[ i ][ j ] == '#' ){
					maiorGeral = j;
					break;
				}
			}
		}
		
		for( int i = 0; i < alt; ++i ){
			for( int j = menorGeral; j <= maiorGeral; ++j ){
				if( painel[ i ][ j ] != '0' ) printf( "%c", painel[ i ][ j ] );
				else printf( "." );
			}
			printf( "\n" );
		}

	}
}







