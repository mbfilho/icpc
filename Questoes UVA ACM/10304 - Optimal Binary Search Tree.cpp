#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define mp make_pair
#define oo 0x7fffffff
#define N 251 
// n³ ~ 2s !!!! Diferença enorme para a versão recursiva!

int custo[ N ], n;
int pd[ N ][ N ];
int acc[ N ];

int faz(){
	for( int i = 0; i < n; ++i )
		pd[ i ][ i ] = 0;
	
	for( int k = 1; k < n; ++k ){
		for( int ini = 0; ini < n - k; ++ini ){
			int fim = ini + k;
			int &menor = pd[ ini ][ fim ];
			menor = oo;
			for( int root = ini; root <= fim; ++root ){
				int esq = 0, dir = 0, somaD = 0, somaE = 0;
				if( root != ini ){
					esq = pd[ ini ][ root - 1 ];
					somaE = acc[ root - 1 ] - acc[ ini ] + custo[ ini ];
				}
				
				if( root != fim ){
					dir = pd[ root + 1 ][ fim ];
					somaD = acc[ fim ] - acc[ root + 1 ] + custo[ root + 1 ];
				}
				
				menor = min( menor, esq + dir + somaD + somaE );
			}
		}
	}
	
	return pd[ 0 ][ n - 1 ];
}


int main(){
	while( scanf( "%d", &n ) != EOF ){
		
		for( int i = 0; i < n; ++i ){
			scanf( "%d", custo + i );
			if( i == 0 )
				acc[ 0 ] = custo[ 0 ];
			else
				acc[ i ] = acc[ i - 1 ] + custo[ i ]; 
		}
		
		printf( "%d\n", faz() );
	}	
}



