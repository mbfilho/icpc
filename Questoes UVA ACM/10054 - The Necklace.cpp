#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 2000
#define COR 160

int ft[ N ], sd[ N ], cont;
vector<int> adj[ COR ];
int at[ COR ];
bool marc[ N ];

void add( int u, int v ){
	ft[ cont ] = u;
	sd[ cont ] = v;
	adj[ u ].push_back( cont );
	adj[ v ].push_back( cont );
//	printf( ">> %d, %d : %d\n", u, v, cont );
	++cont;
}


void euler( int no ){
	
	while( at[ no ] < adj[ no ].size() ){
		int edge = adj[ no ][ at[ no ] ];
		if( !marc[ edge ] ){
			
			int nt = ( ft[ edge ] == no ) ? sd[ edge ] : ft[ edge ];
//			printf( "Visitando %d (%d,%d)\n", edge, no, nt );
			marc[ edge ] = true;
			++at[ no ];
			euler( nt );
			printf( "%d %d\n", nt, no );
		}else
			++at[no];
	}	
}

int main(){
	int casos, n;
	scanf( "%d", &casos );
	
	for( int ca = 1; ca <= casos; ++ca ){
		scanf( "%d", &n );
		for( int i = 0; i <= 50; ++i )
			adj[ i ].clear();
		memset( marc, false, sizeof( marc ) );
		memset( at, 0, sizeof( at ) );
		cont = 0;
		
		int a, b;
		for( int i = 0; i < n; ++i ){
			scanf( "%d %d", &a, &b );
			add( a, b );
		}
		
		bool dm = false;
		for( int i = 0; !dm && i <= 50; ++i ){
			if( adj[ i ].size() & 1 ) dm = true;
		}
		
		printf( "Case #%d\n", ca );
		if( !dm ){
//			printf( ">> %d\n", a );
			euler( a );
		}else
			printf( "some beads may be lost\n" );
		
		if( ca != casos ) printf( "\n" );
	}
}


