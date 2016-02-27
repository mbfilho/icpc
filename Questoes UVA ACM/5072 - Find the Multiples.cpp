#include <stdio.h>
#include <stdlib.h>
#define max_val 100000

typedef long long ll;

int a[ max_val ];


struct Num{
	int val, id, original;
}acc[ max_val ];

typedef struct Num Num;

int n, s, q, w;
int ind[ max_val ];

int comp( const void* a, const void* b ){
	if( ( ( (Num*) a ) -> val ) != ( ( (Num*) b ) -> val ) ){
		return ( (Num*) a ) -> val - ( (Num*) b ) -> val;
	}else
		return ( (Num*) b ) -> id - ( (Num*) a ) -> id;
}

void build(){
	int g = s, i;
	for( i = 0; i < n; i++ ) {
		a[ i ] = ( g / 7 ) % 10;
		
		if( g % 2 == 0 )
			g = g / 2; 
		else 
			g = ( g / 2 ) ^ w;
	}
}

int main(){
	int i;
	
	while( scanf( "%d %d %d %d", &n, &s, &w, &q ) && ( n | s | w | q ) ){
		build();
		long long total = 0;
		
		if( q != 2 && q != 5 ){
			int pot = 10 % q;
			acc[ n - 1 ].val = a[ n - 1 ] % q;
			acc[ n - 1 ].id = n - 1;
			
			for( i = n - 2; i >= 0; --i ){
				acc[ i ].id = i;
				
				acc[ i ].val = ( acc[ i + 1 ].val + pot * a[ i ] ) % q;
				pot = ( pot * 10 ) % q;
			}
			
			
			qsort( acc, n, sizeof( Num ), comp );
			
		
			ind[ 0 ] = 0;
			for( i = 1; i < n; ++i ){
				if( acc[ i ].val == acc[ i - 1 ].val )
					ind[ i ] = ind[ i - 1 ];
				else
					ind[ i ] = i;
			}

			for( i = 0; i < n; ++i ){
				if( a[ acc[ i ].id ] == 0 ) continue;
				
				if( acc[ i ].val ){
					total += i - ind[ i ]; 
				}else{
					total += 1 + i - ind[ i ]; 
				}
			}
		}else if( q == 2 ){
			int zeros = 0;
			
			for( i = 0; i < n; ++i ){
				if( a[ i ] % 2 == 0 ){
					total += i + ( a[ i ] != 0 ) - zeros;
					zeros += ( a[ i ] == 0 );				
				}
			}
		}else{
			int zeros = 0;
			
			for( i = 0; i < n; ++i ){
				if( a[ i ] % 5 == 0 ){
					total += i + ( a[ i ] != 0 ) - zeros;
					zeros += ( a[ i ] == 0 );
				}
			}
		}
		
		printf( "%lld\n", total );
	}
	
	return 0;
}
