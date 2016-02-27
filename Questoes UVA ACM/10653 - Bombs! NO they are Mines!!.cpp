#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
#define N 1100
#define mp make_pair

int dist[ N ][ N ];
int incx[] = { 0, 0, 1, -1 };
int incy[] = { 1, -1, 0, 0 };
queue< pair<int,int> > fila;
int r, c;

int bfs( int a, int b, int fx, int fy ){
	while( !fila.empty() ) fila.pop();
	
	fila.push( mp( a, b ) );
	dist[ a ][ b ] = 0;
	
	while( !fila.empty() ){
		int x = fila.front().first, y = fila.front().second;
		fila.pop();
		//printf( "%d %d\n", x, y );
		
		for( int i = 0; i < 4; ++i ){
			int nx = incx[i] + x, ny = incy[i] + y;
			if( nx < 0 || nx >= r || ny < 0 || ny >= c ) continue;
			if( dist[ nx ][ ny ] != -1 ) continue;
			dist[ nx ][ ny ] = 1 + dist[ x ][ y ];
			
			fila.push( mp( nx, ny ) );  	
		}
	}
	
	return dist[ fx ][ fy ];
}

int main(){
	while( scanf( "%d %d", &r, &c ) != EOF && ( r | c ) ){
		memset( dist, -1, sizeof( dist ) );
		int bombas;
		scanf( "%d", &bombas );
		while( bombas-- ){
			int linha, k, temp;
			scanf( "%d%d", &linha, &k );
			
			while( k-- ){
				scanf( "%d", &temp );
				dist[ linha ][ temp ] = -2;
			}
		}
		
		int x, y, fx, fy;
		scanf( "%d %d %d %d", &x, &y, &fx, &fy );
		
		int resp = bfs( x, y, fx, fy );
		if( resp < 0 ) while(1);
		printf( "%d\n", resp );
	}
}








