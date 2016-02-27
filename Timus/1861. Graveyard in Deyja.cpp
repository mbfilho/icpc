#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
#define N 1001

int pd[ N ][ N ];
char text[ N ], pat[ N ];
int pi[ N ];
int tt, tp;

void calc(){
	tt = strlen( text );
	tp = strlen( pat );
	int k = -1;
	pi[ 0 ] = -1;
	
	for( int i = 1; i < tp; ++i ){
		while( k > -1 && pat[ k + 1 ] != pat[ i ] )
			k = pi[ k ];
			
		if( pat[ k + 1 ] == pat[ i ] ) ++k;
		pi[ i ] = k;
	}
}
char lista[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int memo( int a, int b ){
	int &ret = pd[ a ][ b ];
	if( ret != -1 ) return ret;	

	if( b == tp ){
		if( text[ a ] == '?' ){
			for( int i = 0; lista[ i ]; ++i ){
				text[ a ] = lista[ i ];
				int k = pi[ tp - 1 ];

				while( k > -1 && text[ a ] != pat[ k + 1 ] ) k = pi[ k ];
				if( pat[ k + 1 ] == text[ a ] ) ++k;
				ret = max( ret, memo( a + 1, k + 1 ) );
			}
			
			text[ a ] = '?';
		}else{
			int k = pi[ tp - 1 ];
			
			while( k > -1 && text[ a ] != pat[ k + 1 ] ) k = pi[ k ];
			if( text[ a ] == pat[ k + 1 ] ) ++k;			
			ret = memo( a + 1, k + 1 );
		}
			
		++ret;
	}else if( a >= tt ){
//		printf( "to saindo\n" );
		ret = 0;
	}else if( text[ a ] == '?' ){
		for( int i = 0; lista[ i ]; ++i ){
			text[ a ] = lista[ i ];
			int k = b - 1;
			while( k > -1 && text[ a ] != pat[ k + 1 ] ) k = pi[ k ];
			if( text[ a ] == pat[ k + 1 ] ) ++k;
			
			ret = max( ret, memo( a + 1, k + 1 ) ); 
		}
		text[ a ] = '?';		
	}else{
		int k = b - 1;
		while( k > -1 && text[ a ] != pat[ k + 1 ] ) k = pi[ k ];
		if( text[ a ] == pat[ k + 1 ] ) ++k;
//			printf( "to caindo fora\n" );
		ret = memo( a + 1, k + 1 ); 
	}
	
	return ret;
}

int main(){
	scanf( "%s", text );
	scanf( "%s", pat );
	calc();
	memset( pd, -1, sizeof( pd ) );	
	for( int i = 0; lista[ i ]; ++i )
		rev[ lista[i] ] = i;
	rev[ '?' ] = 52;
	
	printf( "%d\n", memo( 0, 0 ) );	
}


