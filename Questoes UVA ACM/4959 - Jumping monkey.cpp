#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXI (1 << 21)

/*
Faz uma arvore de possiveis locais onde o macaco pode estar e, para cada local deste,
faz o teste atirando. Inicialmente o macaco pode estar em qualquer das 'n' arvores.
Atira-se, em ordem lexicografica, em cada uma dessas arvores. Cada tiro desse gera varios
estados de possiveis locais para o macaco. Cada estado desse é um nó em um grafo maior.
Faça uma busca em largura pelo nó '0', ou seja, o estado que diz que o macaco não pode
estar em local nenhum.
*/

char dist[ MAXI ], shoot[ MAXI ];
int pred[ MAXI ], fila[ MAXI ], head, tail;

vector<int> adj[ 21 ];
int n, m;

int montar( int a, int config ){
	int ret = 0;
	
	for( int i = 0; i < n; ++i ){
		if( i != a && ( config & ( 1 << i ) ) ){
			for( int j = adj[ i ].size() - 1; j >= 0; --j )
				ret = ret | ( 1 << ( adj[ i ][ j ] ) );
		}
	}
	
	return ret;
}

int bfs(){
	int temp, next;
	
	head = 0;
	tail = 1;
	fila[ 0 ] = ( 1 << n ) - 1;
	dist[ fila[0] ] = 0; 
	pred[ fila[0] ] = -1;
	shoot[ fila[0] ] = -1;
	
	while( head < tail ){
		temp = fila[ head++ ];

		if( temp == 0 )
			break;
			
		for( int i = 0; i < n; ++i ){
			if( temp & ( 1 << i ) ){
				next = montar( i, temp );
				if( dist[ next ] == -1 ){
					fila[ tail++ ] = next;
					dist[ next ] = dist[ temp ] + 1;
					pred[ next ] = temp;
					shoot[ next ] = i;
				}
			}
		}
	}
	
	return dist[ 0 ];
}

void print( int a ){
	if( pred[ a ] != -1 ){
		print( pred[ a ] );
		printf( " %d", shoot[ a ] );
	}
}

int main(){
	int a, b;

	while( scanf( "%d %d", &n, &m ) && ( m | n ) ){
		for( int i = 0; i < n; ++i )
			adj[ i ].clear();
			
		fill( dist, dist + ( 1 << n ), -1 );
		
		for( int i = 0; i < m; ++i ){
			scanf( "%d %d", &a, &b );
			adj[ b ].push_back( a );
			adj[ a ].push_back( b );
		}
		
		if( bfs() != -1 ){
			printf( "%d:", dist[ 0 ] );
			print( 0 );
			printf( "\n" );
		}else
			printf( "Impossible\n" );
	}
}
