#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
#define N 200000

string lista[ N ];
int tam, cont;

void faz( char* nome, int prt ){
	if( tam % 2 == 0 && prt + 1 == tam - 1 - prt ){
		for( int i = 0; i < 10; ++i ){
			nome[ prt ] = nome[ prt + 1 ] = i + '0';
			lista[ cont++ ] = nome;
//			printf( "P %s\n", nome );
		}
	}else if( tam % 2 && prt == tam - 1 - prt ){
		for( int i = 0; i < 10; ++i ){
			nome[ prt ] = i + '0';
			lista[ cont++ ] = nome;
//			printf( "I %s\n", nome );
		}
	}else{
		for( int i = 0; i < 10; ++i ){
			nome[ prt ] = nome[ tam - 1 - prt ] = i + '0';
			faz( nome, prt + 1 );
//			printf( "voltei\n" );
		}
	}
}

char linha[ 100 ], nome[ 100 ];
int main(){
	while( scanf( "%s", linha ) != EOF && strcmp( linha, "0" ) ){
		tam = strlen( linha );
		
		bool dm = false;
		for( int i = 0; i < tam / 2; ++i ){
			if( linha[ i ] != linha[ tam - 1 - i ] ) dm = true;
		}
		
		if( !dm ){
			printf( "0\n" );
			continue;
		}
		nome[ tam ] = 0;
		cont = 0;
		faz( nome, 0 );
//		sort( lista, lista + cont );
		
		int ini = 0, fim = cont - 1, meio, best;
		while( ini <= fim ){
			meio = ( ini + fim ) / 2;
			
			if( lista[ meio ] == linha ){
				best = meio;
				break;
			}else if( lista[ meio ] < linha ){
				ini = meio + 1;
			}else{
				best = meio;
				fim = meio - 1;
			}
		}
//		printf( ">> %s\n", linha );		
		long long num = 0, atual = 0;
		for( int i = 0; i < tam; ++i ){
			num = num * 10 + lista[ best ][ i ] - '0'; 
			atual = atual * 10 + linha[ i ] - '0';
//			printf( "%c - %lld\n", linha[i], atual );
		}
//		printf( "%lld\n", atual );
		printf( "%lld\n", num - atual );
	}
}

