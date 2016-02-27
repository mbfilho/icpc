#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
#define N 5100
#define LOGN 13

vector<int> adj[ N ];
int lca[ N ][ LOGN ];
int dist[ N ];

queue<int> fila;
int n;

void bfs(){
	memset( lca, -1, sizeof( lca ) );
	memset( dist, -1, sizeof( dist ) );
	dist[ 1 ] = 0;
	
	while( !fila.empty() ) fila.pop();
	fila.push( 1 );
	
	while( !fila.empty() ){
		int atual = fila.front();
		fila.pop();
		
		for( int i = adj[ atual ].size() - 1; i >= 0; --i ){
			int next = adj[ atual ][ i ];
			if( dist[ next ] != -1 ) continue;
			
			dist[ next ] = 1 + dist[ atual ];
			fila.push( next );
			lca[ next ][ 0 ] = atual;
		}
	}
}

void pro(){
	for( int lg = 1; ( 1 << lg ) <= n; ++lg ){
		for( int i = 1; i <= n; ++i ){
			if( lca[ i ][ lg -1 ] != -1 )
				lca[ i ][ lg ] = lca[ lca[i][lg-1] ][ lg - 1 ];
		}
	}
}

int lcc( int s, int t ){
	if( dist[ s ] > dist[ t ] ) swap( s, t );
	int log = 1;
	while( ( 1 << log ) <= dist[ t ] ) ++log;
	--log;
	
	for( int i = log; i >= 0; --i ){
		if( dist[ t ] - ( 1 << i ) >= dist[ s ] )
			t = lca[ t ][ i ];
	}
	
	if( s == t ) return s;
	log = 1;
	while( ( 1 << log ) <= dist[ t ] ) ++log;
	
	for( log = log - 1; log >= 0; --log ){
		if( lca[ s ][ log ] != lca[ t ][ log ] ){
			s = lca[ s ][ log ];
			t = lca[ t ][ log ];
		}
	}
	
	return lca[ s ][ 0 ];
}


int main(){
	while( scanf( "%d", &n ) != EOF && n ){
		for( int i = 1; i <= n; ++i ) adj[ i ].clear();
		
		for( int i = 1; i < n; ++i ){
			int u, v;
			scanf( "%d %d", &u, &v );
			adj[ u ].push_back( v );
			adj[ v ].push_back( u );
		} 
		
//		printf( "passei\n");
		bfs();
		pro();
		int q;
		scanf( "%d", &q );
		while( q-- ){
			int a, b;
			scanf( "%d %d", &a, &b );
			
			int ances = lcc( a, b );
			int tam = dist[ a ] + dist[ b ] - 2 * dist[ ances ];
			int passo = tam / 2;
//			printf( "LCA %d dist %d\n", ances, tam );
			if( dist[ a ] > dist[ b ] ) swap( a, b );
			int d = passo, pot = 0;
			while( d ){
				if( d & 1 )
					b = lca[ b ][ pot ];
				++pot;
				d = d / 2;
			}
			
			if( tam % 2 ){
				printf( "The fleas jump forever between %d and %d.\n", min( lca[ b ][ 0 ], b ), max( lca[ b ][ 0 ], b ) );
			}else
				printf( "The fleas meet at %d.\n", b );
			
		}
	}	
}





