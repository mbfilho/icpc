#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char bits[ 20 ];
bool marc[ 1 << 17 ];

int main(){
	int a, b, c, s;
	
	while( scanf( "%d", &a ) && a ){
		scanf( "%d %d %d", &b, &c, &s );
		memset( marc, false, sizeof( marc ) );
		int x;
		for( int i = 0; i < 16; ++i ){
			if( s & ( 1 << i ) )
				bits[ i ] = '1';
			else
				bits[ i ] = '0';
		}
		marc[ s ] = true;
		
		x = ( a * s + b ) % c;
		while( !marc[ x ] ){
			for( int i = 0; i < 16; ++i ){
				char b = ( x & ( 1 << i ) ) ? '1' : '0';
				if( bits[ i ] != b )
					bits[ i ] = '?';
			}
			marc[ x ] = true;
			x = ( a * x + b ) % c;
		}
		
		for( int i = 15; i >= 0; --i )
			printf( "%c", bits[ i ] );
		printf( "\n" );
	}
}

