#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

#define N 3*60*600
int n, m, source, sink, cont;

int last[ N ], atual[ N ], res[ N ], pred[ N ], adj[ N ];

void inserir( int a, int b, int cap, bool f = true ){
	pred[ cont ] = last[ a ];
	last[ a ] = cont;
	res[ cont ] = cap;
	adj[ cont ] = b;
	++cont;
	
	if( f )
		inserir( b, a, 0, false );
}

void encher(){
	int saida = n * m;
	int incI[] = { 0, 0, -1, 1 };
	int incJ[] = { -1,1, 0, 0 };	
	for( int i = 0; i < n; ++i ){
		for( int j = 0; j < m; ++j ){
			for( int x = 0; x < 4; ++x ){
				if( i + incI[x] < 0 || i + incI[x] >= n ) continue;
				if( j + incJ[x] < 0 || j + incJ[x] >= m ) continue;
				
				inserir( saida + i * m + j, ( i + incI[x] ) * m + j + incJ[x], 1 );
			}
			
			inserir( i * m + j, saida + i * m + j, 1 ); // entrada -> saida
		}
	}
	source = 2 * n * m;
	sink = source + 1;
	
	for( int j = 0; j < m; ++j ){
		inserir( saida + 0 * m + j, sink, 1 );
		inserir( saida + ( n - 1 ) * m + j, sink, 1 );
	}
	
	for( int i = 0; i < n; ++i ){
		inserir( saida + i * m + 0, sink, 1 );
		inserir( saida + i * m + ( m - 1 ), sink, 1 );
	}
}

int dist[ N ];
bool bfs(){
	memset( dist, -1, sizeof( dist ) );
	for( int i = 0; i <= sink; ++i )
		atual[ i ] = last[ i ];
		
	queue<int> fila;
	fila.push( source );
	dist[ source ] = 0;
	
	while( !fila.empty() ){
		int atual = fila.front();
		fila.pop();
		
		for( int i = last[ atual ]; i != -1; i = pred[ i ] ){
			if( res[ i ] == 0 || dist[ adj[i] ] != -1 ) continue;
			dist[ adj[i] ] = dist[ atual ] + 1;
			fila.push( adj[i] );
			if( adj[i] == sink ) return true;
		}
	}
	
	return false;
}

int dfs( int no, int ac ){
	if( no == sink ) return ac;
	
	for( int& i = atual[ no ]; i != -1; i = pred[ i ] ){
		if( res[ i ] == 0 || ( dist[ no ] + 1 != dist[ adj[i] ] ) ) continue;
		int temp = dfs( adj[i], min( ac, res[ i ] ) );
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
		
		while( (temp = dfs( source, 2000000 )) ){
			//printf( "%d\n", temp );
			flow += temp;
		}
	}
	
	return flow;
}

int main(){
	int casos;
	int a, b, qtd;
	scanf( "%d", &casos );
	
	while( casos-- ){
		memset( last, -1, sizeof( last ) );
		scanf( "%d %d %d", &n, &m, &qtd );
		cont = 0;
		encher();
		
		for( int i = 0; i < qtd; ++i ){
			scanf( "%d %d", &a, &b );
			--a;
			--b;
			inserir( source, a * m + b, 1 );
		}
		
	//	printf( "Qtd %d\n", qtd );
		int maxFlow = dinic();
	//	printf( "Flow %d\n", maxFlow );
		
		if( maxFlow != qtd )
			printf( "not possible\n" );
		else
			printf( "possible\n" );
	}
}





