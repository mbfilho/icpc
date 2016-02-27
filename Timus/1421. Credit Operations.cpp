#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

#define MAX_NO 220

struct No{
	vector<int> adj;
	int atual, dist;
}nos[ MAX_NO ];

int res[ MAX_NO ][ MAX_NO ], sink, source, n;
int fila[ 3 * MAX_NO ];

bool bfs(){
	int ini = 0, fim = 1, next, temp;

	for( int i = 0; i < 2 * n + 2; ++i ){
		nos[ i ].dist = -1;
		nos[ i ].atual = nos[ i ].adj.size() - 1;
	}

	nos[ source ].dist = 0;
	fila[ 0 ] = source;

	while( ini < fim ){
		temp = fila[ ini++ ];
		for( int i = nos[ temp ].adj.size() - 1; i >= 0; --i ){
			next = nos[ temp ].adj[ i ];
			if( nos[ next ].dist == -1 && res[ temp ][ next ] ){
				nos[ next ].dist = nos[ temp ].dist + 1;
				fila[ fim++ ] = next;
				if( next == sink )
					return true;
			}
		}
	}

	return false;
}

int dfs( int no, int acc ){
	if( no == sink ) return acc;
	
	int next, val;
	for( int& i = nos[ no ].atual; i >= 0; --i ){
		next = nos[ no ].adj[ i ];
		if( nos[ next ].dist == nos[ no ].dist + 1 && res[ no ][ next ] ){
			val = dfs( next, min( acc, res[ no ][ next ] ) );
			if( val ){
				res[ no ][ next ] -= val;
				res[ next ][ no ] += val;
				return val;
			} 
		}
	}
	
	return 0;
}

int main(){
	int dado[ 101 ], receb[ 101 ];
	
	while( scanf( "%d", &n ) != EOF ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", receb + i );
		for( int i = 0; i < n; ++i )
			scanf( "%d", dado + i );
			
		for( int i = 0; i < 2 * n + 2; ++i )
			nos[ i ].adj.clear();
			
		memset( res, 0, sizeof( res ) );
		
		source = 2 * n;
		sink = source + 1;
		
		for( int i = 0; i < n; ++i ){
			nos[ source ].adj.push_back( i );
			nos[ i ].adj.push_back( source );
			res[ source ][ i ] = receb[ i ];
		} 
		
		for( int i = n; i < 2 * n; ++i ){
			nos[ sink ].adj.push_back( i );
			nos[ i ].adj.push_back( sink );
			res[ i ][ sink ] = dado[ i - n ];
		}
		
		for( int i = 0; i < n; ++i ){
			for( int j = n; j < 2 * n; ++j ){
				nos[ i ].adj.push_back( j );
				nos[ j ].adj.push_back( i );
				res[ i ][ j ] = 100;
				res[ j ][ i ] = 0;
			}
		}
		int maxFlow = 0;
		
		while( bfs() ){
			int flow = 0;
			while( flow = dfs( source, 10000000 ) )
				maxFlow += flow;
		}
		
		int soma = 0;
		for( int i = 0; i < n; ++i )
			soma += receb[ i ];
				
		if( soma != maxFlow )
			printf( "NO\n" );
		else{
			printf( "YES\n" );
			for( int i = 0; i < n; ++i ){
				for( int j = n; j < 2 * n; ++j )
					printf( "%d%c", res[ j ][ i ], j == 2 * n - 1 ? '\n' : ' ' );
			}
		}
	}
}




