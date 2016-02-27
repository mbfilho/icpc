#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

struct Cam{
	int x, y, id;
}p[ 250100 ];
int cont;

int id1, id2, tam, dir;

bool compX( const Cam& a, const Cam& b ){
	if( a.x == b.x )
		return a.y < b.y;
	return a.x < b.x;
}

bool compY( const Cam& a, const Cam& b ){
	if( a.y == b.y )
		return a.x < b.x;
	return a.y < b.y;
}

int main(){
	int casos;
	char buffer;
	scanf( "%d", &casos );
	
	while( casos-- ){
		id1 = tam = 0x7fffffff;
		id2 = 0xffffffff;
		
		scanf( "%d%*c", &cont );
		
		p[ 0 ].x = p[ 0 ].y = p[ 0 ].id = 0;
		for( int i = 1; i <= cont; ++i ){
			scanf( "%c", &buffer );
			p[ i ].id = i;
			if( buffer == 'W' ){
				p[ i ].y = p[ i - 1 ].y - 1;
				p[ i ].x = p[ i - 1 ].x;
			}else if( buffer == 'E' ){
				p[ i ].x = p[ i - 1 ].x;
				p[ i ].y = p[ i - 1 ].y + 1;
			}else if( buffer == 'S' ){
				p[ i ].x = p[ i - 1 ].x - 1;
				p[ i ].y = p[ i - 1 ].y;
			}else if( buffer == 'N' ){
				p[ i ].x = p[ i - 1 ].x + 1;
				p[ i ].y = p[ i - 1 ].y;
			}				
		}
		sort( p, p + cont + 1, compX );
			
		for( int i = 1; i <= cont; ++i ){
			if( p[ i ].x != p[ i - 1 ].x ) continue;
			if( abs( p[ i ].id - p[ i - 1 ].id ) == 1 ) continue;
			
			if( p[ i ].y - p[ i - 1 ].y < tam ){
				id1 = min( p[ i - 1 ].id, p[ i ].id );
				id2 = max( p[ i - 1 ].id, p[ i ].id );
				tam = p[ i ].y - p[ i - 1 ].y;
				
				if( p[ i ].id > p[ i - 1 ].id )
					dir = 'E';
				else
					dir = 'W';
			}else if( p[ i ].y - p[ i - 1 ].y == tam ){
				int menor = min( p[ i - 1 ].id, p[ i ].id );
				int maior = max( p[ i - 1 ].id, p[ i ].id );
				if( menor < id1 ){
					id1 = menor;
					id2 = maior;
					if( p[ i ].id > p[ i - 1 ].id )
						dir = 'E';
					else
						dir = 'W';
				}else if( menor == id1 && maior > id2 ){
					id2 = maior;
					if( p[ i ].id > p[ i - 1 ].id )
						dir = 'E';
					else
						dir = 'W';
				}
			}
		}
		
		sort( p, p + cont + 1, compY );
			
		for( int i = 1; i <= cont; ++i ){
			if( p[ i ].y != p[ i - 1 ].y  ) continue;
			if( abs( p[ i ].id - p[ i - 1 ].id ) == 1 ) continue;
			
			if( p[ i ].x - p[ i - 1 ].x < tam ){
				id1 = min( p[ i - 1 ].id, p[ i ].id );
				id2 = max( p[ i - 1 ].id, p[ i ].id );
				tam = p[ i ].x - p[ i - 1 ].x;
				
				if( p[ i ].id > p[ i - 1 ].id )
					dir = 'N';
				else
					dir = 'S';
			}else if( p[ i ].x - p[ i - 1 ].x == tam ){
				int menor = min( p[ i - 1 ].id, p[ i ].id );
				int maior = max( p[ i - 1 ].id, p[ i ].id );
				if( menor < id1 ){
					id1 = menor;
					id2 = maior;
					if( p[ i ].id > p[ i - 1 ].id )
						dir = 'N';
					else
						dir = 'S';
				}else if( menor == id1 && maior > id2 ){
					id2 = maior;
					if( p[ i ].id > p[ i - 1 ].id )
						dir = 'N';
					else
						dir = 'S';
				}
			}
		}
		
		printf( "%d %d %d %c\n", tam, id1, id2, char( dir ) );
		if( casos )
			printf( "\n" );
	}
}
