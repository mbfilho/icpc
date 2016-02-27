#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 510

const int front = 0, back = 1, left = 2, right = 3, top = 4, bottom = 5;
const char* pede[] = { "front", "back", "left", "right", "top", "bottom" };
int nos[ N ][ 6 ], n;

int predInd[ N ][ 6 ], predFac[ N ][ 6 ], pd[ N ][ 6 ];
int contra( int f ){
	return f xor 1;
}

int cont( int prt, int face ){
	if( pd[ prt ][ face ] != -1 ) return pd[ prt ][ face ];
	
	predInd[ prt ][ face ] = -1;
	
	int maior = 1;
	for( int i = 0; i < prt; ++i ){
		for( int j = 0; j < 6; ++j ){
			if( nos[i][ j ] == nos[prt][ contra( face ) ] ){
				int aux = 1 + cont( i, j );
				if( aux > maior ){
					predInd[ prt ][ face ] = i;
					predFac[ prt ][ face ] = j;
					maior = aux;				
				}
			}
		}
	}
	
	return pd[ prt ][ face ] = maior;
}

int main(){
	int caso = 1;
	
	while( scanf( "%d", &n ) && n ){
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < 6; ++j )
				scanf( "%d", nos[ n - 1 - i ] + j );
		}
		
		memset( pd, -1, sizeof( pd ) );
		int maior = -1;
		int ind, per;
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < 6; ++j ){
				int aux = cont( i, j );
				if( aux > maior ){
					ind = i;
					per = j;
					maior = aux;
				}
			}
		}
		
		if( caso != 1 )
			printf( "\n" );
		printf( "Case #%d\n", caso++ );
			
		
		printf( "%d\n", maior );
		while( ind != -1 ){
			printf( "%d %s\n", n - 1 - ind + 1, pede[ per ] );
			int t = ind;
			ind = predInd[ t ][ per ];
			per = predFac[ t ][ per ];
		}
	}
}


