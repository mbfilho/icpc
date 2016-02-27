#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <cstdio>
using namespace std;
#define TREE 4000000
int maior[ TREE ], soma[ TREE ], dif[ TREE ];
int n, k;

void build( int no, int ini, int fim ){
	dif[ no ] = 0;		

	if( ini == fim ){
		maior[ no ] = k;
		soma[ no ] = 0;
	}else{
		int meio = ( ini + fim ) / 2;
		build( 2 * no, ini, meio );
		build( 2 * no + 1, meio + 1, fim );
		maior[ no ] = max( maior[ 2 * no ], maior[ 2 * no + 1 ] );
		soma[ no ] = soma[ 2 * no ] + soma[ 2 * no + 1 ];
	}
}

void sub( int no, int ini, int fim, int val ){
	if( ini == fim ){
		maior[ no ] -= val;
		if( !soma[ no ] ){
			++dif[ no ];
			soma[ no ] = k - val;
		}else
			soma[ no ] -= val;
	}else{
		int meio = ( ini + fim ) / 2;
		if( maior[ 2 * no ] >= val )
			sub( 2 * no, ini, meio, val );
		else
			sub( 2 * no + 1, meio + 1, fim, val );
		maior[ no ] = max( maior[ 2 * no ], maior[ 2 * no + 1 ] );
		soma[ no ] = soma[ 2 * no ] + soma[ 2 * no + 1 ];
		dif[ no ] = dif[ 2 * no ] + dif[ 2 * no + 1 ];
	}
}

char tmp[ 30 ];
int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d%d", &k, &n );
		int cont = n;
		build( 1, 1, n );
		while( cont ){
			scanf( "%s", tmp );
			int val;
			if( tmp[ 0 ] >= '0' && tmp[ 0 ] <= '9' ){
				--cont;
				sscanf( tmp, "%d", &val );
				sub( 1, 1, n, val );
			}else{
				int r;
				scanf( "%d %d", &r, &val );
				cont -= r;
				while( r-- )
					sub( 1, 1, n, val );
			}
		}
		printf( "%d %d\n", dif[ 1 ], soma[ 1 ] );
	}
}

