#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 100000
#define TREE 1000000

int num[ N ];
int nos[ TREE ];
int n, q;

int query( int no, int ini, int fim, int a, int b ){
	int meio = ( ini + fim ) / 2;
	if( a == ini && b == fim )
		return nos[ no ];
		
	if( b <= meio )
		return query( 2 * no, ini, meio, a, b );
	else if( a > meio )
		return query( 2 * no + 1, meio + 1, fim, a, b );
	else
		return min( query( 2 * no, ini, meio, a, meio ), query( 2 * no + 1, meio + 1, fim, meio + 1, b ) ); 
}

void alterar( int no, int ini, int fim, int a, int novo ){
	if( ini == fim && fim == a ){
		nos[ no ] = novo;
		num[ ini ] = novo;
		return;
	}
	int meio = ( ini + fim ) / 2;
	
	if( a <= meio ){
		alterar( no * 2, ini, meio, a, novo );
	}else
		alterar( no * 2 + 1, meio + 1, fim, a, novo );
	nos[ no ] = min( nos[ 2 * no ], nos[ 2 * no + 1 ] ); 
}

void build( int no, int ini, int fim ){
	if( ini == fim ){
		nos[ no ] = num[ ini ];
	}else{
		build( no * 2, ini, ( ini + fim ) / 2 );
		build( no * 2 + 1, ( ini + fim ) / 2 + 1, fim );
		nos[ no ] = min( nos[ 2 * no ], nos[ 2 * no + 1 ] );
	}
}

bool dig( char c ){
	return c >= '0' && c <= '9';
}

char linha[ 100 ];
int aux[ 100 ], aux2[ 100 ];
int main(){
	while( scanf( "%d %d", &n, &q ) != EOF  ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", num + i );
		build( 1, 0, n - 1 );
		
		while( q-- ){
			int prt = 0, ind = 0;
			memset( linha, 0, sizeof( linha ) );
			scanf( "%s", linha );

			while( linha[ ind ] ){
				while( linha[ ind ] && !dig( linha[ ind ] ) ) ++ind; 
				if( linha[ ind ] ){
					int temp = 0;
					while( dig( linha[ ind ] ) ){
						temp = temp * 10 + linha[ ind ] - '0';
						++ind;
					}
					aux[ prt++ ] = temp - 1;
				}
			}
			
			if( linha[ 0 ] == 'q' )
				printf( "%d\n", query( 1, 0, n - 1, aux[0], aux[1] ) );
			else{
				for( int i = 0; i < prt; ++i )
					aux2[ i ] = num[ aux[i] ];
				for( int i = 0; i < prt; ++i )
					alterar( 1, 0, n - 1, aux[ i ], aux2[ ( i + 1 ) % prt ] );
			}
		}
	}
}

