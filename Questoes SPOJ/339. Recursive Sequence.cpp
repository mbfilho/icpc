#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MOD 1000000000
#define K 15

typedef long long ll;

int resp[ K ], ma[ K ][ K ];
int temp[K][K], t2[K][K];
int k;

void mult( int dest[K][K], int a[K][K], int b[K][K] ){
	for( int i = 0; i < k; ++i ){
		for( int j = 0; j < k; ++j ){
			ll aux = 0;
			
			for( int x = 0; x < k; ++x )
				aux = ( aux + ll( a[i][x] ) * ll( b[x][j] ) ) % MOD;
			temp[i][j] = int( aux );
		}
	}
	
	for( int i = 0; i < k; ++i ){
		for( int j = 0; j < k; ++j )
			dest[i][j] = temp[i][j];
	}
}

void expo( int a[K][K], int xp ){
	for( int i = 0; i < k; ++i ){
		for( int j = 0; j < k; ++j )
			t2[i][j] = 0;
		t2[i][i] = 1;
	}
	
	while( xp ){
		if( xp & 1 )
			mult( t2, a, t2 );
		mult( a, a, a );
		xp = xp >> 1;
	}
	for( int i = 0; i < k; ++i ){
		for( int j = 0; j < k; ++j )
			a[i][j] = t2[i][j];
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &k );
		for( int i = 0; i < k; ++i )
			scanf( "%d", resp + i );
		
		memset( ma, 0, sizeof ma );
		for( int i = 0; i < k; ++i ){
			if( i < k - 1 )
				ma[ i + 1 ][ i ] = 1;
		}

		for( int i = 0; i < k; ++i )
			scanf( "%d", &ma[ k - 1 - i ][ k - 1 ] );
		
		int n;
		scanf( "%d", &n );
		expo( ma, n - 1 );
		ll resul = 0;
		for( int i = 0; i < k; ++i )
			resul = ( resul + ll( resp[ i ] ) * ll( ma[ i ][ 0 ] ) ) % MOD;
		printf( "%d\n", int( resul ) );
	}
}



