#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define N 15
typedef long long ll;

int pd[ 1001 ];
int peso[ 3001 ], ganho[ 3001 ];

int c0, d0, a[ N ], b[ N ], c[ N ], d[ N ], m, n;

int main(){
	scanf( "%d %d %d %d", &n, &m, &c0, &d0 );
	memset( pd, -1, sizeof( pd ) );
	pd[ 0 ] = 0;
	
	for( int i = 1; i <= m; ++i )
		scanf( "%d %d %d %d", a + i, b + i, c + i, d + i );
	
	a[ 0 ] = n;
	b[ 0 ] = c0;
	c[ 0 ] = c0;
	d[ 0 ] = d0;
	int cont = 0;
	for( int i = 0; i <= m; ++i ){
		for( int j = a[ i ] / b[ i ]; j > 0; --j ){
			peso[ cont ] = c[ i ];
			ganho[ cont++ ] = d[ i ];
		} 
	}
	
	for( int i = 0; i < n / c0; ++i ){
		for( int j = n; j >= c0; --j ){
			if( pd[ j - c0 ] != -1 )
				pd[ j ] = max( pd[ j ], pd[ j - c0 ] + d0 );
		} 
	}
	
	for( int i = 0; i < cont; ++i ){
		for( int j = n; j >= peso[ i ]; --j ){
			if( pd[ j - peso[ i ] ] == -1 ) continue;
			pd[ j ] = max( pd[ j ], pd[ j - peso[ i ] ] + ganho[ i ] );
		}
	}
	
	int maior = -1;
	for( int i = 0; i <= n; ++i )
		maior = max( maior, pd[ i ] );
	printf( "%d\n", maior );
}

