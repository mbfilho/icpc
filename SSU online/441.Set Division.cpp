#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
#define MOD 2007
int K;

void mult( int a[ 20 ][ 20 ], int b[ 20 ][ 20 ], int c[ 20 ][ 20 ] ){
	int tmp[ 20 ][ 20 ];
	
	for( int i = 0; i < K; ++i ){
		for( int j = 0; j < K; ++j ){
			tmp[ i ][ j ] = 0;
			
			for( int h = 0; h < K; ++h )
				tmp[ i ][ j ] = ( tmp[ i ][ j ] + a[ i ][ h ] * b[ h ][ j ] ) % MOD;
		}
	}
	
	for( int i = 0; i < K; ++i ){
		for( int j = 0; j < K; ++j )
			c[ i ][ j ] = tmp[ i ][ j ];
	}
}

void expo( int a[ 20 ][ 20 ], int xp, int b[ 20 ][ 20 ] ){
	int tmp[ 20 ][ 20 ];
	for( int i = 0; i < K; ++i ){
		for( int j = 0; j < K; ++j )
			tmp[ i ][ j ] = 0;
		tmp[ i ][ i ] = 1;
	}
	
	while( xp ){
		if( xp & 1 ) mult( tmp, a, tmp );
		mult( a, a, a );
		xp /= 2;
	}
	
	for( int i = 0; i < K; ++i ){
		for( int j = 0; j < K; ++j )
			b[ i ][ j ] = tmp[ i ][ j ];
	}
}
int n, k;


int ma[ 20 ][ 20 ];

void print(){
	for( int i = 0; i < K; ++i ){
		for( int j = 0; j < K; ++j )
			printf( "%d ", ma[ i ][ j ] );
		printf( "\n" );
	}
	printf( "\n" );
}

int main(){
	scanf( "%d %d", &n, &k );
	K = k + 1;
	memset( ma, 0, sizeof ma );
	for( int j = 0; j < K; ++j ){
		ma[ j ][ j ] = j;
		if( j ) ma[ j - 1 ][ j ] = 1;
	}

//	print();
	expo( ma, n, ma );
//	print();
	
	int resp = ma[ 0 ][ k ];
	
	if( resp < 0 || resp >= 2007 ) throw 1;
	printf( "%d\n", resp );
	
}


