#include <cstdio>
#include <algorithm>
using namespace std;

/*
	Perceba que se a decomposição do numero dado contiver um primo de 2 ou +
	dígitos é impossivel encontrar uma resposta. Imagine que você tenha a fatoração
	prima do número e que seja possivel econtrar a resposta. Como organizar os fatores
	primos de modo a econtar o menor número possivel? Veja um exemplo:
	128 = 2^7 = 2 * 2 * 2 * 2 * 2 * 2 * 2. Cada 3 fatores 2, forme um 8:
	128 = 8 * 8 * 2. Isso garante que o menor número de dígitos possiveis. Agora ordene:
	obtendo 2 * 8 * 8 => 288.
*/

int fatores[ 50 ];
int primos[] =  { 2, 3, 5, 7 };
int cont;

bool preencher( int num ){
	for( int i = 0; i < 50; ++i )
		fatores[ i ] = 1;
	cont = 0;

	for( int pri = 0; pri < 4; ++pri ){
		while( num % primos[ pri ] == 0 ){
			num = num / primos[ pri ];
			if( fatores[ cont ] * primos[ pri ] < 10 )
				fatores[ cont ] *= primos[ pri ];
			else
				fatores[ ++cont ] = primos[ pri ];
		}
	}
	
	if( num != 1 )
		return false;
		
	sort( fatores, fatores + cont + 1 );
	return true;
}

int main(){
	int num;
	int qtd;
	scanf( "%d", &qtd );
	
	while(  qtd-- ){
		scanf( "%d", &num );
		if( num == 0 )
			printf( "0\n" );
		else if( num == 1 )
			printf( "1\n" );
		else if( preencher( num ) ){
			for( int i = 0; i <= cont; ++i )
				printf( "%d", fatores[ i ] );
			printf( "\n" );
		}else
			printf( "-1\n" );
	}
}
