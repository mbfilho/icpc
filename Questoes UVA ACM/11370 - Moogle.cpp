#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 210
#define oo 1e50
int local[ N ];

//atual, qtd
double pd[ N ][ N ];
bool marc[ N ][ N ];
double soma[ N ][ N ];

int n, c;

double rec( int i, int qtd ){
	if( !qtd && i == n - 1 ) return 0;
	if( i == n - 1 ) return oo;
	if( !qtd ) return oo;

	double &resp = pd[ i ][ qtd ];
	if( marc[ i ][ qtd ] ) return resp;

	resp = oo;
		//salvar j
	for( int j = i + 1; j < n; ++j ){
		resp = min( soma[ i ][ j ] + rec( j, qtd - 1 ), resp );
	}
	
	marc[ i ][ qtd ] = true;
	return resp;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &c );
		
		for( int i = 0; i < n; ++i )
			scanf( "%d", local + i );
		
		memset( marc, false, sizeof marc );
		
		for( int i = 0; i < n; ++i ){
			for( int j = i + 1; j < n; ++j ){
				soma[ i ][ j ] = 0;
				
				for( int k = i + 1; k < j; ++k ){
					double temp = local[ i ] + double( local[ j ] - local[ i ] ) * ( k - i ) / double( j - i );
					soma[ i ][ j ] += fabs( local[ k ] - temp );
				}
			}
		}
		
		printf( "%.4lf\n", rec( 0, c - 1 ) / n );
	}
}

