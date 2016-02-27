#include <cstdio>
#include <cstring>

char a[ 200 ], b[ 200 ];

int main(){
	scanf( "%s %s", a, b );
	
	for( int i = 0; a[ i ]; ++i ){
		if( a[ i ] >= 'A' && a[ i ] <= 'Z' ) a[ i ] = a[ i ] - 'A' + 'a';
		if( b[ i ] >= 'A' && b[ i ] <= 'Z' ) b[ i ] = b[ i ] - 'A' + 'a';
	}
	
	int res = strcmp( a, b );
	if( res > 0 )
		printf( "1\n" );
	else if( res < 0 )
		printf( "-1\n" );
	else
		printf( "0\n" );
}

