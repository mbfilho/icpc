#include <cstdio>
#include <algorithm>
using namespace std;

int fibo[ 35 ];

int main(){
	fibo[ 1 ] = 1;
	fibo[ 2 ] = 2;
	
	for( int i = 3; i <= 47; ++i )
		fibo[ i ] = fibo[ i - 1 ] + fibo[ i - 2 ];
	int cont, n;

	scanf( "%d", &cont );
	
	while( cont-- ){
		scanf( "%d", &n );
		printf( "%d = ", n );
		int i = 45;
		
		while( fibo[ i ] > n )
			--i;

		while( n != 0 ){
			if( n >= fibo[ i ] ){
				n -= fibo[ i ];
				printf( "1" );
			}else
				printf( "0" );
			--i;
		}

		for( ; i > 0; --i )
			printf( "0" );
		printf( " (fib)\n" );
	}
}