#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define oo 10000000

char pat[ 20 ][ 20 ], peca[ 20 ][ 20 ];
int n, m;
bool dm;

void faz( char a = '#' ){
	int dx = oo, dy, x = -1, y;
	for( int i = 0; x == -1 && i < n; ++i ){
		for( int j = 0; j < n; ++j ){
			if( pat[ i ][ j ] == '*' ){
				x = i;
				y = j;
				break;
			}
		}
	}
	if( x == -1 ){
		dm = true;
		return;
	}
	
	for( int i = 0; dx == oo && i < m; ++i ){
		for( int j = 0; j < m; ++j ){
			if( peca[ i ][ j ] == '*' ){
				dx = x - i;
				dy = y - j;
				break;
			}
		}
	}
	
	if( dx == oo ){
		dm = true;
		return;
	}
	
	for( int i = 0; !dm && i < m; ++i ){
		for( int j = 0; j < m; ++j ){
			if( peca[ i ][ j ] == '*' ){
				if( i + dx < 0 || j + dy < 0 || i + dx >= n || j + dy >= n || pat[ i + dx ][ j + dy ] != '*' ){
					dm = true;
					break;
				}else
					pat[ i + dx ][ j + dy ] = a;
			}
		}
	}			
}


int main(){
	while( scanf( "%d %d", &n, &m ) != EOF && ( n | m ) ){
		for( int i = 0; i < n; ++i )
			scanf( "%s", pat[ i ] );
		
		for( int i = 0; i < m; ++i )
			scanf( "%s", peca[ i ] );
		
		//Vai 1
		dm = false;
		faz();

		if( !dm )
			faz( '$' );
		for( int i = 0; !dm && i < n; ++i ){
			for( int j = 0; j < n; ++j ){
				if( pat[ i ][ j ] != '.' && pat[i][j] != '#' && pat[i][j] != '$' ){
					dm = true;
					break;
				}
			}
		}
		if( dm )
			printf( "0\n" );
		else
			printf( "1\n" );		
		
	}
}







