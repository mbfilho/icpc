#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 45

ll pd[ N ];
int n, k;

void rec( int tam, int rest ){
	if( tam == 1 ){
		if( rest == 1 ) printf( "0" );
		else printf( "1" );
	}else if( tam == 2 ){
		if( rest == 1 ) printf( "00" );
		else if( rest == 2 ) printf( "01" );
		else printf( "10" );
	}else{
		if( rest <= pd[ tam - 1 ] ){
			printf( "0" );
			rec( tam - 1, rest );
		}else{
			printf( "10" );
			rec( tam - 2, rest - pd[ tam - 1 ] );
		}
	}
}

int main(){
	freopen( "fib.in", "r", stdin );
	freopen( "fib.out", "w", stdout );
//	
	pd[ 1 ] = 2;
	pd[ 2 ] = 3;
		
	for( int i = 3; i < N; ++i ) pd[ i ] = pd[ i - 1 ] + pd[ i - 2 ];
	
	scanf( "%d %d", &n, &k );
	
	rec( n, k );
	printf( "\n" );
	
}



