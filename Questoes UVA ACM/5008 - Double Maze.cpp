#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define N 5010

struct No{
	int l1, l2, c1, c2, dist, acao;
	
	No(){}
	No( int a, int b, int c, int d, int e, int f ){
		l1 = a;
		c1 = b;
		l2 = c;
		c2 = d;
		dist = e;
		acao = f;
	}
};

No pred[ 6 ][ 6 ][ 6 ][ 6 ];

int ma[ 20 ][ 6 ][ 6 ];
int inis[ 20 ][ 2 ];
int fins[ 20 ][ 2 ];

int dist[ 6 ][ 6 ][ 6 ][ 6 ];
int acao[ 6 ][ 6 ][ 6 ][ 6 ];

int m1, m2;

//D L R U
int dl[] = { 1, 0 , 0, -1 };
int dc[] = { 0, -1, 1, 0 };
int mapa[] = { 2, 1, 4, 8 };
const int D = 0, L = 1, R = 2, U = 3;

bool ehHole( int m, int l, int c ){
	return ( ma[ m ][ l ][ c ] & 16 ) == 0;
}

bool pode( No& source, No& dest ){
	No retorno;
	if( dest.l1 > 5 || dest.l1 < 0 || dest.c1 > 5 || dest.c1 < 0 || dest.l2 > 5 || dest.l2 < 0 || dest.c2 > 5 || dest.c2 < 0 ){
		return false;
	}
	
	if( ehHole( m1, dest.l1, dest.c1 ) || ehHole( m2, dest.l2, dest.c2 ) ){
		return false;
	}
	
	return true;
}

void imprimir( No atual ){
	int l1 = atual.l1, c1 = atual.c1, l2 = atual.l2, c2 = atual.c2, act;
	if( l1 == inis[m1][0] && c1 == inis[m1][1] && l2 == inis[m2][0] && c2 == inis[m2][1] ) return;
	//printf( "%d %d %d %d\n", l1, c1, l2, c2 );
	
	imprimir( pred[ l1 ][ c1 ][ l2 ][ c2 ] );
	switch( acao[ l1 ][ c1 ][ l2 ][ c2 ] ){
		case D://Down
			printf( "D" );
			break;
		case U://UP
			printf( "U" );
			break;
		case L:
			printf( "L" );
			break;
		case R:
			printf( "R" );
			break;
	}		
}

int bfs(){
	queue<No> fila;
	memset( dist, -1, sizeof( dist ) );
	memset( acao, -1, sizeof( acao ) );
	fila.push( No( inis[ m1 ][ 0 ], inis[ m1 ][ 1 ], inis[ m2 ][ 0 ], inis[ m2 ][ 1 ], 0, -1 ) );
	dist[ inis[ m1 ][ 0 ] ][ inis[ m1 ][ 1 ] ][ inis[ m2 ][ 0 ] ][ inis[ m2 ][ 1 ] ] = 0;
	
	while( !fila.empty() ){
		No atual = fila.front();
		fila.pop();
		int l1, c1, l2, c2, dista, ac;
		l1 = atual.l1;
		c1 = atual.c1;
		l2 = atual.l2;
		c2 = atual.c2;
		dista = atual.dist;
		ac = atual.acao;
		
		acao[ l1 ][ c1 ][ l2 ][ c2 ] = ac;
		
		for( int act = 0; act < 4; ++act ){
			No destino = atual;
			if( ( ma[ m1 ][ l1 ][ c1 ] & mapa[ act ] ) == 0 ){
				destino.l1 += dl[ act ];
				destino.c1 += dc[ act ];
			} 
			
			if( ( ma[ m2 ][ l2 ][ c2 ] & mapa[ act ] ) == 0 ){
				destino.l2 += dl[ act ];
				destino.c2 += dc[ act ];
			}
			
			++destino.dist;
			destino.acao = act;
			
			if( pode( atual, destino ) ){
				if( dist[ destino.l1 ][ destino.c1 ][ destino.l2 ][ destino.c2 ] == -1 ){
					dist[ destino.l1 ][ destino.c1 ][ destino.l2 ][ destino.c2 ] = dista + 1;
					acao[ destino.l1 ][ destino.c1 ][ destino.l2 ][ destino.c2 ] = act;
					pred[ destino.l1 ][ destino.c1 ][ destino.l2 ][ destino.c2 ] = atual;
					fila.push( destino );
				}
			}
		}

	}
	
	//printf( "A %d\n", acao[ fins[m1][0] ][ fins[m1][1] ][ fins[m2][0] ][ fins[m2][1] ] );
//	imprimir( fins[m1][0], fins[m1][1], fins[m2][0], fins[m2][1] );

	int distancia = dist[ fins[m1][0] ][ fins[m1][1] ][ fins[m2][0] ][ fins[m2][1] ] ;
	if( distancia != -1 )
		imprimir( No( fins[m1][0], fins[m1][1], fins[m2][0], fins[m2][1], 0, acao[ fins[m1][0] ][ fins[m1][1] ][ fins[m2][0] ][ fins[m2][1] ] ) );
		
	return distancia;
}

int main(){
	int mazes;
	scanf( "%d", &mazes );
	
	int temp;
	for( int m = 0; m < mazes; ++m ){
		for( int i = 0; i < 6; ++i ){
			for( int j = 0; j < 6; ++j ){
				scanf( "%d", &temp );
				ma[ m ][ i ][ j ] = temp;
				if( temp & ( 1 << 5 ) ){
					inis[ m ][ 0 ] = i;
					inis[ m ][ 1 ] = j;
				}
				
				if( temp & ( 1 << 6 ) ){
					fins[ m ][ 0 ] = i;
					fins[ m ][ 1 ] = j;
				}
			}
		}
	}
		
	
	m1 = 0;
	m2 = 1;
	while( m2 != mazes ){
		int tam = bfs();
		if( tam != -1 )
			printf( "\n" );
		else
			printf( "-1\n" );
		++m1;
		++m2;
	}
}







