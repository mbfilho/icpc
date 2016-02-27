#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct No{
	int i, j, k;
	
	No( int a, int b, int c ){
		i = a;
		j = b;
		k = c;
	}
};

int ma[ 110 ][ 110 ][ 110 ];
int m;
int incrI[] = { 1, -1, 0, 0, 0, 0 };
int incrJ[] = { 0,  0, 1, -1, 0, 0 };
int incrK[] = { 0, 0,  0, 0,  1, -1 };

queue<No> fila;

void bfs( int a, int b, int c ){
	while( !fila.empty() ) fila.pop();
	fila.push( No( a, b, c ) );
	ma[ a ][ b ][ c ] = 1;
	
	while( !fila.empty() ){
		int i = fila.front().i, j = fila.front().j, k = fila.front().k;
		fila.pop();
		
		for( int x = 0; x < 6; ++x ){
			if( i + incrI[ x ] > 105 || i + incrI[ x ] < 0 ) continue;
			if( j + incrJ[ x ] > 105 || j + incrJ[ x ] < 0 ) continue;
			if( k + incrK[ x ] > 105 || k + incrK[ x ] < 0 ) continue;
			if( ma[ i + incrI[ x ] ][ j + incrJ[ x ] ][ k + incrK[ x ] ] ) continue;
			ma[ i + incrI[ x ] ][ j + incrJ[ x ] ][ k + incrK[ x ] ] = 1;
			fila.push( No( i + incrI[ x ], j + incrJ[ x ], k + incrK[ x ] ) );
		}
	}
	
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &m );
		memset( ma, 0, sizeof( ma ) );
		
		while( m-- ){
			int x, y, z;
			scanf( "%d %d %d", &x, &y, &z );
			ma[ x ][ y ][ z ] = 1;
		}
		
		bfs( 104, 104, 104 );
		int cont = 0;
		for( int i = 1; i <= 100; ++i ){
			for( int j = 1; j <= 100; ++j ){
				for( int k = 1; k <= 100; ++k ){
					if( ma[ i ][ j ][ k ] ) continue;
					++cont;
					bfs( i, j, k );
				}
			}
		}
		
		printf( "%d\n", cont );
	}
}
