#include <cstdio>
#include <algorithm>
using namespace std;

struct bottle{
	int min, max;
}gar[ 200 ];
int cont, litros;

bool val[ 500000 ];

int teto( int a, int b ){
	return (a + b - 1) / b;
}

int main(){
	int casos;
	bool achou;
	scanf( "%d", &casos );
	
	for( int c = 0; c < casos; ++c ){
		scanf( "%d %d", &litros, &cont );
		achou = false;
		litros *= 1000;
		
		for( int i = 0; i < cont; ++i )
			scanf( "%d %d", &gar[ i ].min, &gar[ i ].max );
		
		for( int i = 0; i < cont; ++i ){
			if( litros >= gar[ i ].min * teto( gar[ i ].max, gar[ i ].max - gar[ i ].min ) ){
				printf( "0\n" );
				achou = true;
				break;
			}
		}
		
		if( achou == false ){
			fill( val, val + litros + 1, false );
			val[ 0 ] = true;
			
			for( int i = 0; i < litros; ++i ){
				if( val[ i ] == false ) continue;
				if( val[ litros ] ) break;
				
				for( int j = 0; j < cont; ++j ){
					for( int k = gar[ j ].min; k <= gar[ j ].max; ++k ){
						if( i + k <= litros )
							val[ i + k ] = true;
						else
							break;
					}
				}
			}
				
			int i = litros;
			while( i && val[ i ] == false )
				--i;
			printf( "%d\n", (litros - i) );
		}
		
		if( c != casos - 1 ) printf( "\n" );
	}
}
