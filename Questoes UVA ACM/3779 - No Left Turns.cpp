#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

struct No{
	int x, y, d;
	
	No(){}
	No( int a, int b, int c ){
		x = a;
		y = b;
		d = c;
	}	
};

#define N 30
int dist[ N ][ N ][ 4 ];
char ma[ N ][ N ];
int r, c;

int dir = 0;
int baixo = 1;
int esq = 2;
int cima = 3;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };


int bfs( int a, int b ){
	memset( dist, -1, sizeof( dist ) );
	
	for( int i = 0; i < 4; ++i )
		dist[ a ][ b ][ i ] = 0;
	queue<No> fila;
	
	for( int i = 0; i < 4; ++i ){
		if( a + dx[i] < 0 || a + dx[i] > r ) continue;
		if( b + dy[i] < 0 || b + dy[i] > c ) continue;
		if( ma[ a + dx[i] ][ b + dy[i] ] == 'X' ) continue;
		
		fila.push( No( a + dx[i], b + dy[i], i ) );
		dist[ a + dx[i] ][ b + dy[i] ][ i ] = 1;
	}
	
	
	while( !fila.empty() ){
		No at = fila.front();
		fila.pop();
		
		if( ma[ at.x ][ at.y ] == 'F' ) return dist[ at.x ][ at.y ][ at.d ];
		
		int x = at.x + dx[ at.d ], y = at.y + dy[ at.d ];
		if( x >= 0 && x < r && y >= 0 && y < c && ma[ x ][ y ] != 'X' && dist[ x ][ y ][ at.d ] == -1 ){
			dist[ x ][ y ][ at.d ] = dist[ at.x ][ at.y ][ at.d ] + 1;
			fila.push( No( x, y, at.d ) );
		}
		
		x = at.x + dx[ ( at.d + 1 ) % 4 ];
		y = at.y + dy[ ( at.d + 1 ) % 4 ];
		if( x >= 0 && x < r && y >= 0 && y < c && ma[ x ][ y ] != 'X' && dist[ x ][ y ][ ( at.d + 1 ) % 4 ] == -1 ){
			dist[ x ][ y ][ ( at.d + 1 ) % 4 ] = dist[ at.x ][ at.y ][ at.d ] + 1;
			fila.push( No( x, y, ( at.d + 1 ) % 4 ) );
		}
	}
	
	return -1;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &r, &c );
		
		while( gets( ma[ 0 ] ) && ma[ 0 ][ 0 ] == 0 );
		
		for( int i = 1; i < r; ++i )
			gets( ma[ i ] );
		
		int x, y;
		for( int i = 0; i < r; ++i ){
			for( int j = 0; j < c; ++j ){
				if( ma[ i ][ j ] == 'S' ){
					x = i;
					y = j;
				}
			}
		}
		
		int resp = bfs( x, y );
		printf( "%d\n", resp );
	}
}







