#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define N 2000
#define M 2000
#define oo 0x7fffffff
#define mp make_pair

vector<int> adj[ N ];
int custo[ N ];
bool marc[ N ];
int dist[ N ];

int vida[ 2002 ], aux[ 2001 ];

pair<int,int> magias[ M ];

int m, n, k;

void pre(){
	for( int j = 0; j <= 2000; ++j ){
		vida[ j ] = oo;
		aux[ j ] = oo;
	}
	vida[ 0 ] = 0;

	for( int h = 0; h < m; ++h ){
		int hit = magias[ h ].first, mana = magias[ h ].second;
		for( int j = 0; j <= 1000; ++j ){
			if( vida[ j ] == oo ) continue;
			vida[ j + hit ] = min( vida[ j + hit ], vida[ j ] + mana );
		}
	}
	
	for( int i = 2000; i >= 1000; --i )
		aux[ 1000 ] = min( aux[ 1000 ], vida[ i ] );
	for( int i = 999; i >= 0; --i )
		aux[ i ] = min( aux[ i + 1 ], vida[ i ] );
}

int dij(){
	priority_queue< pair<int,int> > heap;
	heap.push( mp( 0, 1 ) );
	dist[ 1 ] = 0;
	
	while( !heap.empty() ){
		int at = heap.top().second, peso = -heap.top().first;
		heap.pop();
		
		if( marc[ at ] || peso > dist[ at ] ) continue;
		marc[ at ] = true;
		
		for( int i = adj[ at ].size() - 1; i >= 0; --i ){
			int nt = adj[ at ][ i ];
			
			if( !marc[ nt ] && dist[ at ] + custo[ at ] < dist[ nt ] ){
				dist[ nt ] = dist[ at ] + custo[ at ];
				heap.push( mp( -dist[ nt ], nt ) );
			}
		}
	}
	
	return dist[ n ];
}

int main(){
	int g;
	
	while( scanf( "%d %d %d %d", &m, &n, &g, &k ) == 4 && ( n | m | g | k ) ){
		for( int i = 1; i <= n; ++i ){
			adj[ i ].clear();
			custo[ i ] = 0;
			dist[ i ] = oo;
			marc[ i ] = false;
		}
		
		for( int i = 0; i < m; ++i )
			scanf( "%d %d", &magias[ i ].second, &magias[ i ].first );
		pre();
		
		for( int i = 0; i < g; ++i ){
			int u, v;
			scanf( "%d %d", &u, &v );
			adj[ u ].push_back( v );
			adj[ v ].push_back( u );
		}
		
		for( int i = 0; i < k; ++i ){
			int u, hp;
			scanf( "%d %d", &u, &hp );
			custo[ u ] += aux[ hp ];
		}
		
		int resp = dij();
		if( resp == oo )
			printf( "-1\n" );
		else
			printf( "%d\n", resp + custo[ n ] );
	}
}



