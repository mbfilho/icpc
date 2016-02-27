#include <cstdio>
using namespace std;

int bases[ 32 ];
int retornox, retornoy;

class Ponto{
	public:
		int x, y;
}potencias[ 32 ];


void potencia(){
	potencias[ 0 ].x = 1;
	potencias[ 0 ].y = 0;

	for( int i = 1; i <= 31; ++i ){
		potencias[ i ].x = potencias[ i - 1 ].x - potencias[ i - 1 ].y;
		potencias[ i ].y = potencias[ i - 1 ].y + potencias[ i - 1 ].x;
	}

	for( int i = 0; i <= 31; ++i )
		bases[ i ] = 1 << i;
}

Ponto resolver( int numero ){
	for( int i = 0; i <= 31; ++i ){
		if( numero == bases[ i ] )
			return potencias[ i ];
	}

	int pot = 1 << 30;
	int exp = 0;
	for( int i = 1; i <= 31; ++i ){
		if( ( numero & pot ) == 0 ){
			pot = pot >> 1;
		}else
			break;
	}
	
	while( pot >> exp != 1 )
		++exp;
		
	int dif = numero - pot;
	Ponto aux = resolver( 2 * pot - numero );
	Ponto retorno;
	retorno.x = potencias[ exp ].x + ( aux.y - potencias[ exp ].y );
	retorno.y = potencias[ exp ].y - ( aux.x - potencias[ exp ].x );

	return retorno;
}


int main(){
	potencia();
	Ponto aux;
	int buffer;
	scanf( "%d", &buffer );
	
	while( buffer >= 0 ){
		if( buffer == 0 )
			printf( "(0,0)\n" );
		else{
			aux = resolver( buffer );
			printf( "(%d,%d)\n", aux.x, aux.y );
		}
		scanf( "%d", &buffer );
	}

}
