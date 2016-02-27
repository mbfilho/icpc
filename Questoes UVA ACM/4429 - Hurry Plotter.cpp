#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define N 1100
#define oo 1000000000

struct No{
	int y, a, b;
	
	bool operator<( const No& outro ) const{
		if( y != outro.y ) return y < outro.y;
		
		return a < outro.a;
	}
}nos[ N ];

int n, t;
int pd[ N ][ N ];
//pd[k][i] k caras terminando no i-esimo segmento

int main(){
	while( scanf( "%d %d", &n, &t ) != EOF && ( n | t ) ){
		for( int i = 0; i < n; ++i )
			scanf( "%d %d %d", &nos[i].y, &nos[i].a, &nos[i].b );
		sort( nos, nos + n );
		
		int resp = 0;
		for( int i = 0; i < n; ++i ){
			pd[ 1 ][ i ] = nos[ i ].a + 2 * ( nos[ i ].b - nos[ i ].a );
			if( pd[ 1 ][ i ] <= t ) resp = max( resp, 1 );
		}
		
		for( int k = 2; k <= n; ++k ){
			for( int i = 0; i < n; ++i ){
				pd[ k ][ i ] = oo;

				for( int x = 0; x < i; ++x ){
					int custo;
					
					if( nos[ x ].y != nos[ i ].y )
						custo = nos[ x ].b + nos[ i ].a + 2 * ( nos[ i ].b - nos[ i ].a );
					else
						custo = ( nos[ i ].a - nos[ x ].b ) + 2 * ( nos[ i ].b - nos[ i ].a );
					pd[ k ][ i ] = min( pd[ k ][ i ], pd[ k - 1 ][ x ] + custo );
				}
				
				if( pd[ k ][ i ] <= t ) resp = max( resp, k );
			}
			
		}
		
		printf( "%d\n", resp );
	}
}


