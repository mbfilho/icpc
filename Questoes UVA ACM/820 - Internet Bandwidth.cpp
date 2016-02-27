#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 500
#define M 5000000
int cont;
int adj[ M ];
int last[ N ], prev[ M ], atual[ N ], res[ N ];
int s, t, n;

void inserir( int u, int v, int c, bool a = false ){
	prev[ cont ] = last[ u ];
	last[ u ] = cont;
	res[ cont ] = c;
	adj[ cont ] = v;
	++cont;
	
	if( !a )
		inserir( v, u, c, true );
}

int dist[ N ];
bool marc[ N ];

bool bfs(){
	queue<int> fila;
	fila.push( s );
	memset( marc, false, sizeof( marc ) );
	memset( dist, 0, sizeof( dist ) );
	marc[ s ] = true;
		
	while( fila.empty() == false ){
		int atual = fila.front();
		fila.pop();
		
		for( int i = last[ atual ]; i != -1; i = prev[ i ] ){
			int next = adj[ i ];
			if( marc[ next ] || !res[ i ] ) continue;
			
			marc[ next ] = true;
			dist[ next ] = 1 + dist[ atual ];
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

int flow(){
	int maxflow = 0;
	
	while( bfs() ){
		for( int i = 0; i < n; ++i )
			atual[ i ] = last[ i ];
		int flow = 0;
		while( (flow = dfs( s, 0x7fffffff ) ) )
			maxflow += flow;		
	}
	
	return maxflow;
}

int main(){
	int caso = 1;
	
	while( scanf( "%d", &n ) != EOF && n ){
		int m;
		scanf( "%d %d %d", &s, &t, &m );
		--s;
		--t;
		cont = 0;
		memset( last, -1, sizeof( last ) );
		for( int i = 0; i < m; ++i ){
			int u, v, c;
			scanf( "%d %d %d", &u, &v, &c );
			--u;
			--v;
			inserir( u, v, c );
		}
		int f = flow();
		printf( "Network %d\nThe bandwidth is %d.\n\n", caso++, f );
	}
}

