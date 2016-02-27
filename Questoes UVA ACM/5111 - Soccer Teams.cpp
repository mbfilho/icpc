#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXI 0x7fffffff

int num[ 10 ], conj[ 100 ], soma, cont;
int pd[ 901 ][ 101 ][ 51 ];

int dif = MAXI;

int gerar( int soma_m, int dig, int qtd_m ){
	//printf( "Soma: %d Dig: %d qtd: %d\n", soma_m, dig, qtd_m );
	if( qtd_m > cont / 2 ) return MAXI;
	
	if( pd[ soma_m ][ dig ][ qtd_m ] != MAXI )
		return pd[ soma_m ][ dig ][ qtd_m ];
			
	int menor, maior;
	if( qtd_m > cont - qtd_m ){
		maior = qtd_m;
		menor = cont - qtd_m;
	}else{
		maior = cont - qtd_m;
		menor = qtd_m;
	}
	
	int zeros = MAXI;
			
	if( abs( 2 * soma_m - soma ) % 11 == 0 ){
		if( maior == menor ){
			return pd[ soma_m ][ dig ][ qtd_m ] = 0;
		}
		
		zeros = maior - ( menor + 1 );
	}
		
//	for( int k = dig; k < cont; ++k ){
		if( dig < cont ){
			zeros = min( zeros, gerar( soma_m + conj[ dig ], dig + 1, qtd_m + 1 ) );
			zeros = min( zeros, gerar( soma_m, dig + 1, qtd_m  ) );
		}
//	}
	
	return pd[ soma_m ][ dig ][ qtd_m ] = zeros;
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		soma = cont = 0;
		int tam = 0;
		
		for( int i = 1; i < 10; ++i ){
			scanf( "%d", num + i );
			cont += num[ i ];
			soma += i  * num[ i ];
			
			for( int j = 0; j < num[ i ]; ++j )
				conj[ tam++ ] = i;
		}
		
		
		
		for( int i = 0; i <= soma; ++i ){
			for( int j = 0; j <= cont; ++j ){
				for( int k = 0; k <= cont / 2; ++k )
					pd[ i ][ j ][ k ] = MAXI;
			}
		}
		
		
		int aux = gerar( 0, 0, 0 );
		//int aux = 0;
		if( aux == MAXI )
			printf( "-1\n" );
		else
			printf( "%d\n", cont + aux );
	}
}
