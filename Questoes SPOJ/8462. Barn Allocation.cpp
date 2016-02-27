#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100000
#define TREE 1000000
#define oo 0x7fffffff

int menor[ TREE ], ops[ TREE ];
int num[ N ];

void makeTree( int no, int ini, int fim ){
	ops[ no ] = 0;
	
	if( ini == fim ){
		menor[ no ] = num[ ini ]; 
//		printf( "(%d,%d): %d\n", ini, fim, menor[ no ] );
	}else{
		int meio = ( ini + fim ) / 2;
		makeTree( 2 * no, ini, meio );
		makeTree( 2 * no + 1, meio + 1, fim );
		menor[ no ] = min( menor[ 2 * no ], menor[ 2 * no + 1 ] );
//			printf( "(%d,%d): %d\n", ini, fim, menor[ no ] );
	}
}

void ajeitar( int no ){
	menor[ no ] -= ops[ no ];
	ops[ 2 * no ] += ops[ no ];
	ops[ 2 * no + 1 ] += ops[ no ];
	ops[ no ] = 0;
}

int query( int no, int ini, int fim, int a, int b ){
	ajeitar( no );
//	if( b < ini || a > fim ) return oo; 
	int meio = ( ini + fim ) / 2;
	
	if( a <= ini && b >= fim ){
		return menor[ no ];
	}else if( b <= meio ){
		return query( 2 * no, ini, meio, a, b );
	}else if( a >= meio + 1  ){
		return query( 2 * no + 1, meio + 1, fim, a, b );
	}else{
		int resp;
		resp = query( 2 * no, ini, meio, a, meio );
		resp = min( resp, query( 2 * no + 1, meio + 1, fim, meio + 1, b ) );
				
		return resp;
	}
}

void decrementar( int no, int ini, int fim, int a, int b ){
	ajeitar( no );
	int meio = ( ini + fim ) / 2;
	if( b < ini || a > fim ) return;
	
	if( a <= ini && b >= fim ){
		++ops[ no ];
		ajeitar( no );
	}else{
		decrementar( 2 * no, ini, meio, a, b );
		decrementar( 2 * no + 1, meio + 1, fim, a, b );
		menor[ no ] = min( menor[ 2 * no ], menor[ 2 * no + 1 ] );
	}
}

pair<int,int> inter[ N ];
int n, m;

int main(){
	scanf( "%d %d", &n, &m );
	for( int i = 0; i < n; ++i )
		scanf( "%d", num + i );
	makeTree( 1, 0, n - 1 );
	for( int i = 0; i < m; ++i )
		scanf( "%d %d", &inter[ i ].second, &inter[ i ].first );
	
	sort( inter, inter + m );
	int resp = 0;
	for( int i = 0; i < m; ++i ){
		int ini = inter[ i ].second - 1, fim = inter[ i ].first - 1;
		int r = query( 1, 0, n - 1, ini, fim );
//		printf( "%d-%d: %d\n", ini+1, fim+1, r ); 
		if( r > 0 ){
			decrementar( 1, 0, n - 1, ini, fim );
//			printf( "%d\n", i );
			++resp;
		}
	}
	printf( "%d\n", resp );
	
	
}





