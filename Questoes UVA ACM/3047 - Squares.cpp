#include <cstdio>
#include <algorithm>
using namespace std;

/*
Compactação de coordenadas.
*/
struct Ponto{
	int x, y;
}p[ 1000 ];

int cont, id;

int mapx[ 40000 ], mapy[ 40000 ], valx[ 40000 ], valy[ 40000 ];
int grid[ 1000 ][ 1000 ];

inline bool compX( const Ponto& a, const Ponto& b ){
	return a.x < b.x;
}

inline bool compY( const Ponto& a, const Ponto& b ){
	return a.y < b.y;
}

int main(){
	id = 0;
	for( int i = 0; i < 1000; ++i ){
		for( int j = 0; j < 1000; ++j )
			grid[ i ][ j ] = 0;
	}
	
	for( int i = 0; i < 40000; ++i )
		mapx[ i ] = mapy[ i ] = 0;
	
	while( scanf( "%d", &cont ) && cont ){
		++id;
		for( int i = 0; i < cont; ++i ){
			scanf( "%d %d", &p[ i ].x, &p[ i ].y );
			p[ i ].x += 20000;
			p[ i ].y += 20000;
		}
		sort( p, p + cont, compX );
		
		mapx[ p[ 0 ].x ] = 0;
		valx[ p[ 0 ].x ] = id;
		int ind = 0;
		for( int i = 1; i < cont; ++i ){
			if( p[ i ].x != p[ i - 1 ].x ){
				++ind;
				mapx[ p[ i ].x ] = ind;
				valx[ p[ i ].x ] = id;
			}
		}
		
		sort( p, p + cont, compY );
		
		mapy[ p[ 0 ].y ] = 0;
		valy[ p[ 0 ].y ] = id;
		grid[ mapx[ p[ 0 ].x ] ][ 0 ] = id;
		ind = 0;
		for( int i = 1; i < cont; ++i ){
			if( p[ i ].y == p[ i - 1 ].y )
				grid[ mapx[ p[ i ].x ] ][ ind ] = id;
			else{
				++ind;
				mapy[ p[ i ].y ] = ind;
				valy[ p[ i ].y ] = id;
				grid[ mapx[ p[ i ].x ] ][ ind ] = id;
			}
		}
		
		int x, y, qtd = 0;
		for( int i = 0; i < cont - 1; ++i ){
			for( int j = i + 1; j < cont; ++j ){
				x = p[ j ].x - p[ i ].x;
				y = p[ j ].y - p[ i ].y;
				
				if( ( x + y ) & 1 ) continue;
				if( ( y - x ) & 1 ) continue;
				
				int a = x;
				x = p[ i ].x + ( x + y ) / 2;
				y = p[ i ].y + ( y - a ) / 2;
				if( valx[ x ] == id && valy[ y ] == id ){
					if( grid[ mapx[ x ] ][ mapy[ y ] ] == id ){
						x = p[ j ].x - ( x - p[ i ].x );
						y = p[ j ].y - ( y - p[ i ].y );
						
						if( valx[ x ] == id && valy[ y ]== id ){
							if( grid[ mapx[ x ] ][ mapy[ y ] ] == id )
								++qtd;
						}
					}
						
				}
			}
		}
		
		printf( "%d\n", qtd / 2 );
	}
}
