#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 100100
#define MOD 5000000

int bit[ 51 ][ MAXN ];

void update( int b, int x, int val ){
	for( int i = x; i < MAXN; i += ( i & -i ) )
		bit[ b ][ i ] = ( bit[ b ][ i ] + val ) % MOD;
}

int query( int b, int x ){
	int soma = 0;
	for( int i = x; i > 0; i -= ( i & -i ) )
		soma = ( bit[ b ][ i ] + soma ) % MOD;
	
	return soma;	
}

int n, k;
int num[ 10100 ];
int main(){
		
	while( scanf( "%d %d", &n, &k ) != EOF ){
		for( int i = 0; i < n; ++i ){
			scanf( "%d", num + i );
			++num[ i ];
		}
		
		memset( bit, 0, sizeof( bit ) );
		
		for( int ind = n - 1; ind >= 0; --ind ){
			
			update( 0, num[ ind ], 1 );
			for( int i = 0; i < k - 1; ++i ){
				int s = query( i, MAXN - 1 ) - query( i, num[ ind ] );
				while( s < 0 ) s += MOD;
				update( i + 1, num[ ind ], s );
			}
		}
		
		printf( "%d\n", query( k - 1, MAXN - 1 ) );
			
	}
}




