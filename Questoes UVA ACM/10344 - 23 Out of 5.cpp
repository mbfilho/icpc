#include <algorithm>
#include <cstdio>
using namespace std;

/*
Dado que os operadores estão em locais 'fixos' da expressão, testar todas as possíveis
combinações dos operandos. Como são 5 operandos, o total de combinações a serem testadas
é igual a 5! = 720, que é bem pouco. Se alguma delas der certo, obviamente a respostas é
Possible. Caso contrario, Impossible.
*/
int nums[ 5 ];

bool responder( int ind, int ant ){
	if( ind == 5 )
		return ant == 23;

	int a1, a2, a3;
	a1 = ant + nums[ ind ];
	a2 = ant * nums[ ind ];
	a3 = ant - nums[ ind ];

	return ( responder( ind + 1, a1 ) || responder( ind + 1, a2 ) || responder( ind + 1, a3 ) );
}


int main(){
	bool possible;

	while( true ){
		int controle = 0;
		for( int i = 0; i < 5; ++i ){
			scanf( "%d", &nums[ i ] );
			controle = controle | nums[ i ];
		}
		
		if( !controle ) break;
		
		sort( nums, nums + 5 );
		possible = false;
		
		do{
			if( responder( 1, nums[ 0 ] ) ){
				possible = true;
				break;
			}
			
		}while( next_permutation( nums, nums + 5 ) );

		if( possible )
			printf( "Possible\n" );
		else
			printf( "Impossible\n" );


	}
}
