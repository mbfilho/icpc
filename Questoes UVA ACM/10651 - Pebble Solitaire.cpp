#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define oo 0x7fffffff

int pd[ 1 << 13 ];

int faz( int mask ){
	if( pd[ mask ] != -1 ) return pd[ mask ];
	
	int &menor = pd[ mask ];
	menor = 0;
	for( int i = 0; i < 12; ++i ){
		if( mask & ( 1 << i ) )
			++menor;
	}
	
	for( int i = 0; i < 10; ++i ){
		//o o -
		if( mask & ( 1 << i ) ){
			if( mask & ( 1 << ( i + 1 ) ) ){
				if( !( mask & ( 1 << ( i + 2 ) ) ) ){
					int newMask = mask | ( 1 << ( i + 2 ) );
					newMask = newMask & ( ~(1 << ( i + 1 ) ) );
					newMask = newMask & ( ~(1 << i) );
					menor = min( menor, faz( newMask ) );
				}
			}
		}
		
		//- o o
		if( !( mask & ( 1 << i ) ) ){
			if( mask & ( 1 << ( i + 1 ) ) ){
				if( mask & ( 1 << ( i + 2 ) ) ){
					int newMask = mask & ( ~( 1 << ( i + 2 ) ) );
					newMask = newMask & ( ~( 1 << ( i + 1 ) ) );
					newMask = newMask | ( 1 << i );
					menor = min( menor, faz( newMask ) );
				}
			}
		}
		
		
	}
	
	return menor;
}

int main(){
	char linha[ 100 ];
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%s", linha );
		int mask = 0;
		for( int i = 0; linha[ i ]; ++i ){
			if( linha[ i ] == 'o' )
				mask |= ( 1 << i );
		}
		
		memset( pd, -1, sizeof( pd ) );
		printf( "%d\n", faz( mask ) );
	}
}




