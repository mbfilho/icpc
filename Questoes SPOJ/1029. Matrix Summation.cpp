#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1100

int bit[ N ][ N ];
int n;

void update( int x, int y, int val ){
	for( int i = x; i <= n; i += ( i & -i ) ){
		for( int j = y; j <= n; j += ( j & -j ) )
			bit[ i ][ j ] += val;
	}
}

int soma( int x, int y ){
	int s = 0;
	
	for( int i = x; i > 0; i -= ( i & -i ) ){
		for( int j = y; j > 0; j -= ( j & -j ) ){
			s += bit[ i ][ j ];
		}
	}	
	
	return s;
}

char op[ 100 ];

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &n );
		memset( bit, 0, sizeof( bit ) );
		
		while( scanf( "%s", op ) && op[ 0 ] != 'E' ){
			if( strcmp( op, "SET" ) == 0 ){
				int x, y, val;
				scanf( "%d %d %d", &x, &y, &val );
				++x;
				++y;
				
				int at = soma( x, y ) - soma( x, y - 1 ) - soma( x - 1, y ) + soma( x - 1, y - 1 );
				update( x, y, val - at );
			}else{
				int x1, y1, x2, y2;
				scanf( "%d %d %d %d", &x1, &y1, &x2, &y2 );
				++y1;
				++y2;
				++x1;
				++x2;
				int s = soma( x2, y2 ) - soma( x2, y1 - 1 ) - soma( x1 - 1, y2 ) + soma( x1 - 1, y1 - 1 );
				
				printf( "%d\n", s );
			}
		}
		printf( "\n" );
		 
	}
}

 
