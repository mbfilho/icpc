#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define N 110

bool marc[ N ];
int pilha[ N ], sp;
vector<int> adj[ N ];
bool ciclo[ N ];
bool achou = false;
int n, m;

void dfs( int no, int pai ){
	marc[ no ] = true;
	
	for( int i = adj[ no ].size() - 1; !achou && i >= 0; --i ){
		if( adj[no][i] == pai ) continue;
		if( marc[ adj[no][i] ] ){
			achou = true;
			int temp;
			do{
				temp = pilha[ --sp ];
				ciclo[ temp ] = true;
			}while( temp != adj[no][i] );
			break;
		}
		
		pilha[ sp++ ] = adj[ no ][ i ];
		dfs( adj[ no ][ i ], no );
		--sp;
	}
}

bool ehArv( int no, int pai ){
	marc[ no ] = true;
	bool resp = true;
	
	for( int i = adj[ no ].size() - 1; resp && i >= 0; --i ){
		if( ciclo[ adj[no][i] ] || adj[no][i] == pai ) continue;
		if( marc[ adj[no][i] ] ) return false;
		resp = resp && ehArv( adj[no][i], no );
	}
	
	return resp;
}

bool eh(){
	bool resp = true;
	for( int i = 0; resp && i < n; ++i ){
		if( !ciclo[ i ] ) continue;
		memset( marc, false, sizeof( marc ) );
		resp = resp && ehArv( ciclo[ i ], -1 );
	}
	
	return resp;
}

int conexo( int no, int pai ){
	marc[ no ] = true;
	int ret = 0;
	
	for( int i = adj[ no ].size() - 1; i >= 0; --i ){
		if( adj[no][i] == pai ) continue;
		if( marc[ adj[no][i] ] ) ++ret;
		else
			ret += conexo( adj[no][i], no );
	}
	
	return ret;
}

int main(){
	scanf( "%d %d", &n, &m );
	for( int i = 0; i < m; ++i ){
		int u, v;
		scanf( "%d %d", &u, &v );
		--u;
		--v;
		adj[ u ].push_back( v );
		adj[ v ].push_back( u );
	}
	
	memset( marc, false, sizeof( marc ) );
	memset( ciclo, false, sizeof( ciclo ) );
	
	pilha[ 0 ] = 0;
	sp = 1;
	dfs( 0, -1 );
	
	memset( marc, false, sizeof( marc ) );
	int num = conexo( 0, -1 );
	bool dm = num > 2; //conta se tem mais de 1 ciclo
	for( int i = 0; !dm && i < n; ++i )
		dm = dm || !marc[ i ];

	if( !achou || dm )
		printf( "NO\n" );
	else{
		if( eh() )
			printf( "FHTAGN!\n" );
		else
			printf( "NO\n" );
		
	}
}
