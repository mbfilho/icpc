#include <cstdio>
#include <cstring>

#include <algorithm>
using namespace std;

char ma[ 20 ][ 20 ];
int n, m;
int incx[] = { 1, -1, 0, 0 };
int incy[] = { 0, 0, 1, -1 };

int main(){
	memset( ma, 0, sizeof( ma ) );
	scanf( "%d %d", &n, &m );
	for( int i = 1; i <= n; ++i )
		scanf( "%s", ma[ i ] + 1 );
	
	int cont = 0;
	for( int i = 1; i <= n; ++i ){
		for( int j = 1; j <= m; ++j ){
			if( ma[ i ][ j ] == 'P' ){
				for( int k = 0; k < 4; ++k ){
					if( ma[ i + incx[k] ][ j + incy[k] ] == 'W' ){
						ma[ i + incx[k] ][ j + incy[k] ] = 0;
						++cont;
						break;
					}
				}
			}
		}
	}
	
	printf( "%d\n", cont );
}
