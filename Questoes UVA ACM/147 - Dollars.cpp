#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
#define MAX 6001

typedef long long ll;
ll valor[ MAX ];
int moedas[] = { 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

void preencher(){
//Esse for transforma as unidades. A moeda de 5 vira moeda de 1. A moeda de 20 vira 4
//e assim sucessivamente:
	for( int i = 0; i < 9; ++i )
		moedas[ i ] = moedas[ i ] / 5;
		
//Preenche os "caso base" da pd. Como todos os valores serão multiplos de 5,
//o array[i] guarda o numero de formas de trocar i * 5 dolares. Com isso, 
//todo i pode ser formado de 1 forma( 1 moeda de 5). i / 2 indica quantas formas
//um valor pode ser trocado em moedas de 10.
	for( int i = 0; i < MAX; ++i ){
		valor[ i ] = 1;
		valor[ i ] +=  i / 2;
	}

		
	for( int i = 0; i < 9; ++i ){
		for( int j = moedas[ i ]; j < MAX; ++j )
			valor[ j ] += valor[ j - moedas[ i ] ];
	}
}

int potencias[ 10 ];
int getCents( char *val ){
	int pot = 0, len = strlen( val );
	int retorno = 0;
	
	for( int i = len - 1; i >= 0; --i ){
	//	cout << val[ i ] << " ";
		if( val[ i ] != '.' )
			retorno += (val[ i ] - '0') * potencias[ pot++ ];
	}
	
	return retorno;
}

int main(){
	char val[ 201 ];
	int cents;
	cout.precision( 2 );
	cout.setf( ios::fixed );
	
	potencias[ 0 ] = 1;
	for( int i = 1; i < 10; ++i )
		potencias[ i ] = potencias[ i - 1 ] * 10;
		
	preencher();

	
	while( cin >> val && strcmp( val, "0.00" ) ){
		cents = getCents( val );
		cout.width( 6 );
		cout.setf( ios::right );
		cout << val;
		cout.width( 17 );
		cout.setf( ios::right );
		cout << valor[ cents / 5 ] << endl;
	}
}
