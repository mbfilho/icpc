#include <cstdio>

int main(){
	int n;
	scanf( "%d", &n );
	
	int qt = 10000000, st = -1;
	
	for( int i = n / 7; i >= 0; --i ){
		if( ( n - i * 7 ) % 4 == 0 ){
			int a = ( n - i * 7 ) / 4;
			if( i + a == qt + st && i < st ){
				qt = a;
				st = i;
			}else if( i + a < qt + st ){
				qt = a;
				st = i;
			}
		}
	}
	
	if( st == -1 )
		printf( "-1\n" );
	else{
		for( int i = 0; i < qt; ++i )
			printf( "4" );
		for( int i = 0; i < st; ++i )
			printf( "7" );
		printf( "\n" );
	}
}

