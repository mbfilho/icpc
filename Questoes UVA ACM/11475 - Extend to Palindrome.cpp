#include <cstdio>
#include <cstring>
typedef unsigned long long ull;

char s1[ 100001 ];
ull pot1[ 100000 ];

int b1 = 107;

void preencher(){
	pot1[ 0 ] = 1;
	
	for( int i = 1; i < 100000; ++i )
		pot1[ i ] = ( pot1[ i - 1 ] * b1 );
}

int rk(){
	int prt, inv, tam;
	tam = strlen( s1 );
	inv = prt = tam - 1;
	ull h1 = 0, hi1 = 0;
	
	int retorno = -1;
	while( inv >= 0 ){
		hi1 = ( hi1 * b1 + s1[ inv ] );		
		h1 = ( h1 + s1[ prt ] * pot1[ tam - 1 - prt ] );
		
		if( hi1 == h1 )
			retorno = prt;
					
		--prt;
		--inv;
	}
	
	return retorno;
}

int main(){
	preencher();
	int indice;
	
	while( scanf( "%s", s1 ) != EOF ){
		indice = rk() - 1;
		printf( "%s", s1 );

		while( indice >= 0 ){
			printf( "%c", s1[ indice ] );
			--indice;
		}
		
		printf( "\n" );
	}
}
