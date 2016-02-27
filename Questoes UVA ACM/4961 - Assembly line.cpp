#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
#define INFI 100000000

/*
Muito parecido com a pd da multiplicação de matrizes ( matriz chain ).
A diferença é que faz parte do estado o caracter que a parentização (i..j) forma.
*/
int car[ 26 ][ 26 ]; //Matriz de montagem, c1 montado com c2 forma car[c1][c2].
int tempo[ 26 ][ 26 ]; //Tempo para montar c1 com c2 é tempo[ c1 ][ c2 ].
int pd[ 200 ][ 200 ][ 26 ]; //PD[i][j][k] guarda o tempo otimo para montar de (i..j) formando a peça k.
char seq[ 300 ]; //A sequecia a ser montada;
int n; //Tamanho da sequecia a ser montada;
int tipo[ 200 ];//Desncessário =P. Tipo[i] guarda seq[i] - 'a'.
int val[ 26 ]; //Guarda quais caracteres podem aparecer na sequencia
int ind[ 26 ]; //ind[i] guarda o indice, na entrada, do caracter i + 'a'. Serve para avaliar os empates.

void faz(){
	int resultante;
	for( int i = 0; i < n; ++i ){
		for( int j = 0; j < n; ++j ){
			for( int k = 0; k < 26; ++k )
				pd[ i ][ j ][ k ] = INFI;
		}
	}
	
	for( int i = 0; i < n - 1; ++i ){
		resultante = car[ tipo[i] ][ tipo[i + 1] ];
		pd[ i ][ i + 1 ][ resultante ] = tempo[ tipo[i] ][ tipo[i + 1] ];
	}
	
	for( int i = 0; i < n; ++i ){
		pd[ i ][ i ][ tipo[i] ] = 0;
	}	
	
	for( int tam = 3; tam <= n; ++tam ){
		for( int i = 0; i + tam - 1 < n; ++i ){
			int j = i + tam - 1;
			
			for( int k = i; k < j; ++k ){
				for( int c1 = 0; c1 < 26; ++c1 ){
					if( pd[ i ][ k ][ c1 ] >= INFI ) continue;
					
					for( int c2 = 0; c2 < 26; ++c2 ){
						if( pd[ k + 1 ][ j ][ c2 ] >= INFI ) continue;
						resultante = car[ c1 ][ c2 ];
						pd[ i ][ j ][ resultante ] = min( pd[ i ][ j ][ resultante ],pd[ i ][ k ][ c1 ] + pd[ k + 1 ][ j ][ c2 ] + tempo[ c1 ][ c2 ] );
					}
				}
			}
		}
	}
}

int main(){
	int k, t;
	char buf;
	
	scanf( "%d\n", &k );
	while( k ){
		for( int i = 0; i < k; ++i ){
			scanf( "%c ", &buf );
			val[ i ] = buf - 'a';
			ind[ val[i] ] = i;
		}
		
		for( int i = 0; i < k; ++i ){
			for( int j = 0; j < k; ++j ){
				scanf( "%d-%c", &t, &buf );
				car[ val[i] ][ val[j] ] = buf - 'a';
				tempo[ val[i] ][ val[j] ] = t;
			}
		}
		
		scanf( "%d", &t );
		for( int i = 0; i < t; ++i ){
			scanf( "%s", seq );
			n = strlen( seq );
			for( int i = 0; i < n; ++i )
				tipo[ i ] = seq[ i ] - 'a';
			faz();
			int temp = 0x7fffffff;
			for( int i = 0; i < 26; ++i ){
				if( pd[ 0 ][ n - 1 ][ i ] < INFI ){
					if( pd[ 0 ][ n - 1 ][ i ] < temp ){
						temp = pd[ 0 ][ n - 1 ][ i ];
						buf = i + 'a';
					}else if( pd[ 0 ][ n - 1 ][ i ] == temp ){
						if( ind[ i ] < ind[ buf - 'a' ] ){
							buf = i + 'a';
						}
					}
				}
			}
			
			printf( "%d-%c\n", temp, buf );
		}
		
		scanf( "%d\n", &k );
		if( k )
			printf( "\n" );
	}
}
