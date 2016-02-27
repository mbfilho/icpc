#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
#define N 50100
#define M 100100
#define LOG 16
vector<int> adj[ N ];
int ft[ M ], sc[ M ], peso[ M ], edges[ M ];
int n, m;

int conj[ N ];

int find( int a ){
	if( a != conj[ a ] )
		conj[ a ] = find( conj[ a ] );
	return conj[ a ];
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

bool comp( const int& a, const int& b ){
	return peso[ a ] < peso[ b ];
}

void kruskal(){
	for( int i = 0; i < n; ++i )
		conj[ i ] = i;
	
	sort( edges, edges + m, comp );
	
	for( int i = 0; i < m; ++i ){
		int a = edges[ i ];
		if( find( ft[ a ] ) == find( sc[ a ] ) ) continue;
		unir( ft[ a ], sc[ a ] );
		adj[ ft[a] ].push_back( a );
		adj[ sc[a] ].push_back( a );
	}	
}

int level[ N ], pai[ N ][ LOG ], are[ N ][ LOG ];
void bfs( int raiz ){
	level[ raiz ] = 0;
	queue<int> fila;
	fila.push( raiz );
	
	while( fila.empty() == false ){
		int atual = fila.front();
		fila.pop();
		
		for( int i = adj[ atual ].size() - 1; i >= 0; --i ){
			int next;
			if( sc[ adj[atual][i] ] != atual )
				next = sc[ adj[atual][i] ];
			else
				next = ft[ adj[atual][i] ];
				
			if( level[ next ] != -1 ) continue;
			level[ next ] = level[ atual ] + 1;
			pai[ next ][ 0 ] = atual;
			are[ next ][ 0 ] = peso[ adj[atual][i] ];
			fila.push( next );
		}
	}
	
}

void lca(){
	for( int j = 1; (1 << j) <= n; ++j ){ 
		for( int i = 0; i < n; ++i ){
			are[ i ][ j ] = are[ i ][ j - 1 ];
			
			if( pai[i][j-1] != -1 && pai[ pai[i][j - 1] ][ j - 1 ] != -1 ){
				pai[ i ][ j ] = pai[ pai[i][j - 1] ][ j - 1 ];
				are[ i ][ j ] = max( are[ i ][ j ], are[ pai[i][j-1] ][ j - 1 ] );
			}
		}
	}
}

int query( int a, int b ){
	if( level[ a ] < level[ b ] )
		swap( a, b );
	
	int maior = -1;
	if( level[ a ] > level[ b ] ){
		int log = 1;
		while( ( 1 << log ) <= level[ a ] ) ++log;
		--log;
		
		for( int i = log; i >= 0; --i ){
			if( level[ a ] - ( 1 << i ) >= level[ b ] ){
				maior = max( maior, are[ a ][ i ] );
				a = pai[ a ][ i ];
			}
		}
	}
	
	if( a != b ){
		int log = 1;
		while( ( 1 << log ) <= level[ a ] ) ++log;
		--log;
		for( int i = log; i >= 0; --i ){
			if( pai[ a ][ i ] != pai[ b ][ i ] ){
				maior = max( maior, are[ a ][ i ] );
				a = pai[ a ][ i ];
				
				maior = max( maior, are[ b ][ i ] );
				b = pai[ b ][ i ];
			}
		}
		
		maior = max( maior, are[ a ][ 0 ] );
		maior = max( maior, are[ b ][ 0 ] );
	}
	
	return maior;
}

int main(){
	bool f = true;
	
	while( scanf( "%d %d", &n, &m ) != EOF ){
		if( f ) f = false;
		else printf( "\n" );
		
		for( int i = 0; i < n; ++i ) adj[i].clear();
		
		for( int i = 0; i < m; ++i ){
			scanf( "%d %d %d", ft + i, sc + i, peso + i );
			edges[ i ] = i;
			--ft[i];
			--sc[i];
		}
		
		kruskal();
		/*
		printf( "AGPM\n" );
		for( int i = 0; i < n; ++i ){
			printf( "Adj de %d: ", i + 1 );
			for( int j = adj[i].size() - 1; j >= 0; --j )
				printf( "(%d-%d),", ft[ adj[i][j] ], sc[ adj[i][j] ] );
			printf( "\n" );
		}
		*/
		for( int i = 0; i < n; ++i ){
			level[ i ] = -1;
			for( int j = 0; ( 1 << j ) <= n; ++j )
				pai[ i ][ j ] = -1;
		}
		//memset( are, -1, sizeof( are ) );
		bfs(0);
		/*for( int i = 0; i < n; ++i ){
			if( level[ i ] == -1 )
				bfs( i );
		}*/
		lca();
		int q;
		scanf( "%d", &q );
		
		while( q-- ){
			int a, b;
			scanf( "%d %d", &a, &b );
			--a;
			--b;
			int r = query( a, b );
			//if( r == -1 ) throw 1;
			printf( "%d\n", query( a, b ) );
		}		
	}
}




