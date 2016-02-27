#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 110
#define mp make_pair
#define oo 100000000
int n, m;
int ft[ N ], sd[ N ];
int peso[ N ][ N ];

vector<int> adj[ N ];

void dij( int a ){
	for( int i = 0; i < n; ++i )
		ft[ i ] = sd[ i ] = oo;

	priority_queue< pair<int,int> > heap;
	heap.push( mp( 0, a ) );
	ft[ a ] = 0;
	
	while( !heap.empty() ){
		int at = heap.top().second, p = -heap.top().first;
		heap.pop();
		if( p > sd[ at ] ) continue;
		
		for( int i = adj[ at ].size() - 1; i >= 0; --i ){
			int nt = adj[ at ][ i ], wei = peso[ at ][ nt ];
			if( p + wei < ft[ nt ] ){
				sd[ nt ] = ft[ nt ];
				ft[ nt ] = p + wei;
				heap.push( mp( -p - wei, nt ) );
			}else if( p + wei > ft[ nt ] && p + wei < sd[ nt ] ){
				sd[ nt ] = p + wei;
				heap.push( mp( -p - wei, nt ) );
			}
		}
	}
	
}


int main(){
	int caso = 1;
	
	while( scanf( "%d %d", &n, &m ) == 2 ){
		for( int i = 0; i < n; ++i ) adj[i].clear();
		
		for( int i = 0; i < m; ++i ){
			int u, v, p;
			scanf( "%d %d %d", &u, &v, &p );
			peso[ u ][ v ] = peso[ v ][ u ] = p;
			adj[ u ].push_back( v );
			adj[ v ].push_back( u );
		}
		
		printf( "Set #%d\n", caso++ );u
		int q;
		scanf( "%d", &q );
		while( q-- ){
			int u, v;
			scanf( "%d %d", &u, &v );
			dij( u );
			
			if( sd[ v ] == oo )
				printf( "?\n" );
			else
				printf( "%d\n", sd[ v ] );
		}
	}
}



