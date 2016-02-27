#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 100
//Que problema bugado =P

char ma[ N + 1 ][ N + 1 ];
char a[ 50 ], b[ 50 ];

int main(){
	while( scanf( "%s %s", a, b ) != EOF && ( strcmp( a, "0" ) || strcmp( b, "0" )  ) ){
			
		for( int i = 0; i < N; ++i ){
			ma[ i ][ N ] = 0;
			for( int j = 0; j < N; ++j )
				ma[ i ][ j ] = ' ';
		}
				
		int aa = strlen( a ), bb = strlen( b );
		for( int i = 0; i < aa; ++i )
			ma[ 0 ][ N-1 - aa + 1 + i ] = a[ i ];
		
		for( int i = 0; i < bb; ++i )
			ma[ 1 ][ N-1 - bb + 1 + i ] = b[ i ];
			
		for( int i = 0; i < max( aa, bb ); ++i)
			ma[ 2 ][ N-1 - i ] = '-';
			
				
		int lin = 3, col = N-1, prt;
		
		for( int i = bb - 1; i >= 0; --i ){
			 for( int k = aa - 1, j = col; k >= 0; --k, --j ){
			 	if( b[ i ] == '1' )
				 	ma[ lin ][ j ] = a[ k ]; 
				 else
				 	ma[ lin ][ j ] = '0';
			 }
			 ma[ lin ][ col + 1 ] = 0;
			 --col;
			 ++lin;
		}
		for( int i = 0; i < N; ++i )
			ma[ lin ][ i ] = '-';
		++lin;

		ll na = 0, nb = 0, res;
		for( int i = 0; i < aa; ++i )
			na = na * 2 + a[ i ] - '0';
		for( int i = 0; i < bb; ++i )
			nb = nb * 2 + b[ i ] - '0';

		res = na * nb;
		for( prt = N-1; res; --prt ){
			if( res & 1LL )
				ma[ lin ][ prt ] = '1';
			else
				ma[ lin ][ prt ] = '0';
			res /= 2;
		} 
		for( ; prt > col + 1 - aa; --prt )
			ma[ lin ][ prt ] = '0';
		
		++lin;
		
		for( int i = 0; i < lin; ++i )
			printf( "%s\n", prt + ma[ i ] + 1 );
		
		printf( "\n" );

	}
}









