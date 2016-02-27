#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 1500
#define G 200
int n, t, g;

int peso[ N ], preco[ N ];

int pd[ 50 ];

int knap( int cap ){
	memset( pd, 0, sizeof( pd ) );
	
	for( int i = 0; i < n; ++i ){
		for( int j = cap; j >= 0; --j ){
			if( j >= peso[ i ] )
				pd[ j ] = max( pd[ j ], pd[ j - peso[ i ] ] + preco[ i ] );
		}
	}
	
	return pd[ cap ];
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &n );
		for( int i = 0; i < n; ++i ){
			scanf( "%d %d", preco + i, peso + i );
		}
		
		scanf( "%d", &g );
		int soma = 0;
		for( int i = 0; i < g; ++i ){
			int cap;
			scanf( "%d", &cap );
			soma += knap( cap );
		}
		printf( "%d\n", soma );
		
	}
}


