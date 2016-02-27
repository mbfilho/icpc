#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

#define N 5100
#define MOD 100000
vector<int> adj[ N ];
int ordem[ N ], prt, n, m;
bool marc[ N ];
int paths[ N ], teams[ N ];

void dfs( int no ){
	marc[ no ] = true;
	
	for( int i = adj[ no ].size() - 1; i >= 0; --i ){
		if( !marc[ adj[no][i] ] )
			dfs( adj[ no ][ i ] );
	}
	
	ordem[ prt++ ] = no;
}

void solve( int caso ){
	prt = 0;
	dfs( 1 );
	paths[ 1 ] = 1;
	teams[ 1 ] = 0;
	
//	for( int i = prt - 1;  i >= 0; --i )
//		printf( "%d ", ordem[ i ] );
		
	for( int i = prt - 1; i >= 0; --i ){
		for( int j = adj[ ordem[i] ].size() - 1; j >= 0; --j ){
			paths[ adj[ ordem[i] ][j] ] = ( paths[ adj[ ordem[i] ][j] ] + paths[ ordem[i] ] ) % MOD;
			teams[ adj[ ordem[i] ][j] ] = ( teams[ adj[ ordem[i] ][j] ] + paths[ ordem[i] ] + teams[ ordem[i] ] ) % MOD;
		}
	}
	
	printf( "Case %d: %d %d\n", caso, teams[ n ], paths[ n ] );
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int caso = 1; caso <= casos; ++caso ){
		scanf( "%d %d", &n, &m );
		int u, v;
		
		for( int i = 1; i <= n; ++i ){
			adj[ i ].clear();
			paths[ i ] = teams[ i ] = marc[ i ] = 0;
		}
		
		for( int i = 0; i < m; ++i ){
			scanf( "%d %d", &u, &v );
			adj[ u ].push_back( v );
		}
		
		solve( caso );
	}
}





