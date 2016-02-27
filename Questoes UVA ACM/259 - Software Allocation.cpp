#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 1000
#define M 1000

int sc[ M ], atual[ N ], pred[ M ], res[ M ], last[ N ], nedge;
int dist[ N ];

void inserir( int a, int b, int cap, bool f = true ){
	pred[ nedge ] = last[ a ];
	sc[ nedge ] = b;
	res[ nedge ] = cap;
	last[ a ] = nedge;
	++nedge;
	
	if( f )
		inserir( b, a, 0, false );
}

bool bfs( int source, int sink ){
	memset( dist, -1, sizeof( dist ) );
	queue<int> fila;
	fila.push( source );
	dist[ source ] = 0;

	while( fila.empty() == false ){
		int atual = fila.front();
		fila.pop();
		
		for( int i = last[ atual ]; i != -1; i = pred[ i ] ){
			if( res[ i ] == 0 || dist[ sc[i] ] != -1 ) continue;
			dist[ sc[ i ] ] = dist[ atual ] + 1;
			fila.push( sc[ i ] ); 
			if( sc[ i ] == sink ) return true;
		}
	}
	
	return false;
	
}

int dfs( int no, int aum, int sink ){
	if( no == sink ) return aum;
	
	for( int& i = atual[ no ]; i != -1; i = pred[ i ] ){
		if( res[ i ] == 0 || ( dist[ sc[i] ] != dist[ no ] + 1 ) ) continue;
		int c = dfs( sc[i], min( aum, res[i] ), sink );
		if( c ){
			res[i] -= c;
			res[i xor 1] += c;
			return c;
		}
	}
	
	return 0;
}

int dinic( int source, int sink ){
	int flow = 0;
	
	while( bfs( source, sink ) ){
		for( int i = 0; i < 38; ++i )
			atual[ i ] = last[ i ];
		int temp;
		while( ( temp = dfs( source, 2000, sink ) ) )
			flow += temp;
	}
	
	return flow;
}

int main(){
	int source = 36, sink = 37;
	char buf[ 1000 ];
	
	while( gets( buf ) ){
		memset( last, -1, sizeof( last ) );
		nedge = 0;
		int soma = 0;
		
		do{
			char c;
			int cap;
			sscanf( buf, "%c%d", &c, &cap ); 
			soma += cap;
			inserir( source, c - 'A', cap );
			for( int i = 3; buf[ i ] != ';'; ++i )
				inserir( c - 'A', buf[ i ] - '0' + 26, 1 );
		}while( gets( buf ) && buf[ 0 ] );
		
		for( int i = 0; i < 10; ++i )
			inserir( i + 26, sink, 1 );
				
		int flow = dinic( source, sink );
	//	printf( "F: %d Soma %d\n", flow, soma );
		if( flow != soma )
			printf( "!\n" );
		else{
			for( int i = 0; i < 10; ++i ){
				char imp = '_';
				for( int j = last[ i + 26 ]; j != -1; j = pred[ j ] ){
					if( sc[ j ] != sink && res[ j ] ){
						imp = sc[ j ] + 'A';
						break;
					} 
				}
				printf( "%c", imp );
			}
			printf( "\n" );
		}
		
	}
	
}



