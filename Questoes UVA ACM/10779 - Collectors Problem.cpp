#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 50
#define M 2000

int adj[ M ], res[ M ], prev[ M ];
int last[ N ], atual[ N ];
int dist[ N ];
int cont;
int s, t;

void inserir( int u, int v, int cap, bool p = true ){
	prev[ cont ] = last[ u ];
	last[ u ] = cont;
	adj[ cont ] = v;
	res[ cont ] = cap;
	++cont;
	
	if( p ) inserir( v, u, 0, false );
}

bool bfs(){
	queue<int> fila;
	memset( dist, -1, sizeof( dist ) );
	for( int i = 0; i <= t; ++i )
		atual[ i ] = last[ i ];
		
	fila.push( s );
	dist[ s ] = 0;
	
	while( !fila.empty() ){
		int atual = fila.front();
		fila.pop();
		
		for( int i = last[ atual ]; i != -1; i = prev[ i ] ){
			int next = adj[ i ];
			if( dist[ next ] != -1 || !res[ i ] ) continue;
			
			dist[ next ] = dist[ atual ] + 1;
			fila.push( next );
			if( next == t ) return true;
		}
	}
	
	return false;
}

int dfs( int no, int cap ){
	if( no == t ) return cap;
	
	for( int& i = atual[ no ]; i != -1; i = prev[ i ] ){
		if( !res[ i ] || dist[ no ] + 1 != dist[ adj[i] ] ) continue;
		int temp = dfs( adj[ i ], min( cap, res[ i ] ) );
		if( temp ){
			res[ i ] -= temp;
			res[ i xor 1 ] += temp;
			return temp;
		}
	}
	
	return 0;
}

int dinic(){
	int flow = 0;
	
	while( bfs() ){
		int temp;
		while( temp = dfs( s, 0x7fffffff ) )
			flow += temp;
	}
	
	return flow;
}

int qtd[ 100 ], pt[ 100 ];

int sticks[ 30 ][ 30 ];

int main(){
	int casos;
	int n, m;
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%d %d", &n, &m );
		cont = 0;
		s = m + n;
		t = s + 1;
		memset( sticks, 0, sizeof( sticks ) );
		memset( last, -1, sizeof( last ) );
		
		for( int i = 0; i < n; ++i ){
			int k;
			scanf( "%d", &k );
			while( k-- ){
				int temp;
				scanf( "%d", &temp );
				++sticks[ i ][ temp - 1 ];
			}
		}
		
		for( int i = 0; i < m; ++i )
			inserir( i, t, 1 );
		for( int i = 0; i < m; ++i ){
			if( sticks[ 0 ][ i ] )
				inserir( s, i, sticks[ 0 ][ i ] );
		}
		
		for( int i = 0; i < m; ++i ){
			for( int pes = 1; pes < n; ++pes ){
				//Pessoa pes n tem o stick i
				if( !sticks[ pes ][ i ] )
					inserir( i, m + pes, 1 );
			}
		}
		for( int i = 1; i < n; ++i ){
			for( int j = 0; j < m; ++j ){
				if( sticks[ i ][ j ] > 1 )
					inserir( m + i, j, sticks[ i ][ j ] - 1 );
			}
		}
		int flow = dinic();
		printf( "Case #%d: %d\n", c, flow );
	}
	
}


