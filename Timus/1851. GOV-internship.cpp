#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define M 2000000
#define N 3000

int pred[ M ], res[ M ], ft[ M ], sd[ M ];
int atual[ N ], last[ N ], dist[ N ];
int cont;
char text[ N ], pat[ N ];
int n;

void add( int u, int v, int cap, bool b = true ){
	pred[ cont ] = last[ u ];
	last[ u ] = cont;
	res[ cont ] = cap;
	ft[ cont ] = u;
	sd[ cont ] = v;
	++cont;
	if( b ) add( v, u, cap, false );
}

queue<int> fila;

bool bfs( int source, int sink ){
	while( !fila.empty() ) fila.pop();
	memset( dist, -1, sizeof( dist ) );
	for( int i = 0; i < n; ++i ) atual[ i ] = last[ i ];
	 
	dist[ source ] = 0;
	fila.push( source );
	
	while( !fila.empty() ){
		int at = fila.front();
		fila.pop();
		for( int ed = atual[ at ]; ed != -1; ed = pred[ ed ] ){
			if( dist[ sd[ed] ] == -1 && res[ ed ] ){
				dist[ sd[ed] ] = dist[ at ] + 1;
				if( sd[ed] == sink ) return true;
				fila.push( sd[ed] );
			} 
		}
	}
	
	return false;
}

int dfs( int no, int sink, int menor ){
	if( no == sink ) return menor;
	
	for( int& i = atual[ no ]; i != -1; i = pred[ i ] ){
		if( !res[ i ] || dist[ no ] + 1 != dist[ sd[i] ] ) continue;
		int temp = dfs( sd[i], sink, min( menor, res[i] ) );
		if( temp ){
			res[ i ] -= temp;
			res[ i xor 1 ] += temp;
			
			return temp;
		}
	}
	
	return 0;
}

int dinic( int source, int sink ){
	int maxflow = 0, flow;
	
	while( bfs( source, sink ) ){
		while( (flow = dfs( source, sink, 20000000 ) ) )
			maxflow += flow;
	}
	
	return maxflow;
}

void busca( int no ){
	dist[ no ] = 1;
	
	for( int i = last[ no ]; i != -1; i = pred[i] ){
		if( dist[ sd[i] ] || !res[ i ] ) continue;
		busca( sd[i] );
	}
}

int main(){
	scanf( "%s%s", text, pat );
	memset( last, -1, sizeof( last ) );
	cont = 0;
	int tt = strlen( text ), tp = strlen( pat );
	int source = tt + tp, sink = source + 1;
	n = sink + 1;
	
	for( int i = 0; i + tp <= tt; ++i ){
		for( int j = 0; j < tp; ++j ){
			if( text[ i + j ] != '?' && pat[ j ] != '?' ){
				if( text[ i + j ] != pat[ j ] ) add( source, sink, 1 );
			}else if( text[ i + j ] == '?' ){
				if( pat[ j ] == '0' ) add( source, i + j, 1 );
				else if( pat[ j ] == '1' ) add( sink, i + j, 1 );
				else add( i + j, tt + j, 1 );
			}else if( pat[ j ] == '?' ){
				if( text[ i + j ] == '0' ) add( source, tt + j, 1 );
				else if( text[ i + j ] == '1' ) add( sink, tt + j, 1 );
			}
		}
	}
	int qtd = dinic( source, sink );
	printf( "%d\n", qtd );
	memset( dist, 0, sizeof( dist ) );
	busca( source );
	for( int i = 0; i < tt; ++i ){
		if( text[ i ] == '?' ){
			if( dist[ i ] ) text[ i ] = '0';
			else text[ i ] = '1';
		}
	}
	
	for( int i = 0; i < tp; ++i ){
		if( pat[ i ] == '?' ){
			if( dist[ tt + i ] ) pat[ i ] = '0';
			else pat[ i ] = '1';
		}
	}
	printf( "%s\n%s\n", text, pat );
}




