#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define pb 	push_back
#define N 160000
#define K 310
#define oo 1000000000

int filhos[ N ];
int perm[ N ], valor[ N ];
vector<int> adj[ N ];

int cont, n, k;

int rec( int raiz ){
	perm[ cont++ ] = raiz;
	
	filhos[ raiz ] = 1;
	for( int i = 0; i < adj[ raiz ].size(); ++i ){
		filhos[ raiz ] += rec( adj[ raiz ][ i ] );
	}
	
	return filhos[ raiz ];
}

int pd[ N ][ K ];

//separar os vértices em grupos e junta-los com knapsack =D
int main(){
	int raiz;
	
	while( scanf( "%d %d", &n, &k ) != EOF ){
		for( int i = 1; i <= n; ++i ) adj[ i ].clear();
		
		for( int i = 1; i <= n; ++i ){
			int pai;
			scanf( "%d %d", &pai, valor + i );
			if( !pai ) raiz = i;
			else adj[ pai ].pb( i );
		}
		
		cont = 1;
		rec( raiz );
//		for( int i = 1; i <= n; ++i ){
//			printf( ">> %d %d %d\n", perm[i], filhos[perm[i]], valor[perm[i]] );
//		}
//		
		for( int i = 1; i <= n + 1; ++i ){
			for( int j = 0 ; j <= k; ++j ) pd[ i ][ j ] = -oo;
			pd[i][0] = 0;
		}
		
		pd[ n ][ 1 ] = valor[ perm[n] ];
		
		for( int i = n - 1; i > 0; --i ){
			int next = filhos[ perm[i] ];
			
			for( int j = 1; j <= k; ++j ){
				pd[ i ][ j ] = pd[ i + next ][ j ];
				
				if( pd[ i + next ][ j - 1 ] != -oo )
					pd[ i ][ j ] = max( pd[ i ][ j ], valor[ perm[i] ] + pd[ i + next ][ j - 1 ] );
			}
			
			for( int j = 0; j <= k; ++j )
				pd[ i ][ j ] = max( pd[ i ][ j ], pd[ i + 1 ][ j ] );
		}
//		printf( ">>>> %d\n", pd[1][k] );
		
		if( pd[ 1 ][ k ] >= 0 ) 
			printf( "%d\n", pd[ 1 ][ k ] );
		else printf( "impossible\n" ); 
		
	}
}


